#include "ximuapi/gl/gl_context.h"
#include <QSurfaceFormat>
#include <iostream>
#include <QOpenGLFunctions_4_0_Core>

namespace ximu{

GlContext::GlContext() :
    _msleep(100), _state(UN_INITIALIZED),_rendererId(0),_surfacePtr(0)
{}

GlContext::~GlContext()
{
    _state = State::CLOSING;
    _thread.join();
    _state = State::CLOSED;
}

void GlContext::create()
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_state == State::UN_INITIALIZED)
    {
        bool useq = true;
        if (useq)
        {
            std::thread tmp(&GlContext::run,this);
            _thread.swap(tmp);
            _state = State::ACTIVE;
        }else
        {
            connect(&_qthread,SIGNAL(started()),this,SLOT(run()));
            _qthread.start();
        }
    }
}

void GlContext::run()
{
    _active = true;
    _ctx = std::unique_ptr<QOpenGLContext>(new QOpenGLContext);

    QSurfaceFormat format;
    format.setMajorVersion(4);
    format.setMinorVersion(0);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);
    _ctx->setFormat(format);
    _active = _ctx->create();
    _ctx->makeCurrent(0);

    while(_active)
    {
        switch(_state)
        {
            case State::CLOSE:
                _state = State::CLOSING;
                _active = false;
            break;
            case State::ACTIVE:            
                if (_surfacePtr)
                {
                    for (auto& ren : _renderers)
                        ren.second->render();
                    _ctx->swapBuffers(_surfacePtr);
                }
            break;
        }

        {
            std::lock_guard<std::mutex> lock(_mutex);
            while(!_tasks.empty())
            {
                _tasks.front()();
                _tasks.pop();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(_msleep));
    }
}

void GlContext::destroy()
{
    std::lock_guard<std::mutex> lock(_mutex);
    _tasks.push([&]{_active = false;});
}


void GlContext::pMakeCurrent(QSurface* surface)
{
    std::cout << "Points!" << surface << std::endl;
    if (_ctx->isValid())
        if (_ctx->makeCurrent(surface))
            _surfacePtr = surface;

}

void GlContext::makeCurrent(QSurface* surface)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _tasks.push([=]
    {
        this->pMakeCurrent(surface);
    });
}

size_t GlContext::add(std::shared_ptr<IGlRenderer> renderer)
{
    std::lock_guard<std::mutex> lock(_mutex);
    ++_rendererId;
    _renderers[_rendererId] =renderer;
    _tasks.push([=]{renderer->initializeGL(_ctx);});
    return _rendererId;
}

}
