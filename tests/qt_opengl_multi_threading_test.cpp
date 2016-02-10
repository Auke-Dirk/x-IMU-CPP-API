/*
  Copyright 2015 Auke-Dirk Pietersma
*/
#include <tuple>
#include <vector>
#include <thread>
#include <memory>
#include <QDebug>
#include <QScreen>
#include <QWindow>
#include <QApplication>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_0_Core>

#include "ximuapi/gl/gl_context.h"


/* Simple Renderer */
class SmoothRenderer : public ximu::IGlRenderer
{
private:
    QOpenGLFunctions_4_0_Core* GL;
    bool _isInitalized = false;
    GLfloat value = 0;    
public:
    virtual void initializeGL(std::unique_ptr<QOpenGLContext>& ctx)
    {
        GL = ctx->versionFunctions<QOpenGLFunctions_4_0_Core>();
        if (!GL){
              qFatal("Requires OpenGL >= 4.0");
        }
        else
        {
          GL->initializeOpenGLFunctions();
            _isInitalized = true;
        }
    }
    void render()
    {
        if (_isInitalized)
        {
            value += 0.1;
            if (value > 1.0)
                value = 0.0;
            GL->glClearColor(value, 0.0, value, 0.0);
            GL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }
    }
};


typedef std::unique_ptr<ximu::GlContext> CTX_TYPE;
typedef std::unique_ptr<QWindow> WINDOW_TYPE;
typedef std::tuple<CTX_TYPE,WINDOW_TYPE> DATA_TYPE;

int main(int argc, char *argv[])
{
    // Main Application
    QGuiApplication a(argc, argv);

    QWindow t;
    t.show();

    // Generate a some Contexts with Windows
    std::vector<DATA_TYPE> data;
    for (size_t idx = 0; idx != 5; ++idx)
        data.push_back(std::move(std::make_tuple(CTX_TYPE(new ximu::GlContext()), WINDOW_TYPE(new QWindow))));

    // Initialize
    for(auto& d : data)
    {
       std::get<0>(d)->create();
       std::get<1>(d)->setSurfaceType(QWindow::OpenGLSurface);
       std::get<1>(d)->show();
    }

    // Assume application runtime
    size_t numCalls = 1000;
    size_t calls = numCalls;
    std::thread closer( [&] {
        while(--calls  > 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if (calls == (numCalls - 10))
            {
                for(auto& d : data){
                    // attach Surface to Context
                    std::get<0>(d)->makeCurrent(std::get<1>(d).get());
                    std::get<0>(d)->add(std::shared_ptr<ximu::IGlRenderer>(new SmoothRenderer));
               }
            }
        }
        // Destroy context, close window
        for(auto& d : data)
        {
          std::get<0>(d)->destroy();
          QMetaObject::invokeMethod(std::get<1>(d).get(), "close", Qt::QueuedConnection);
        }
        QMetaObject::invokeMethod(&t, "close", Qt::QueuedConnection);

    });


    auto retcode =  a.exec();

    closer.join();

    return retcode;
}
