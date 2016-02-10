#ifndef XIMUAPI_GL_GL_CONTEXT_H
#define XIMUAPI_GL_GL_CONTEXT_H

#include <thread>
#include <mutex>
#include <QOpenGLContext>
#include <memory>
#include <queue>
#include <map>
#include <ximuapi/gl/igl_renderer.h>
#include <QThread>

namespace ximu{
    class GlContext : public QObject
    {
        Q_OBJECT
    public:
       enum  State { UN_INITIALIZED,ACTIVE, CLOSE, CLOSING, CLOSED};

    private:
        bool _active;
        State _state;
        size_t _msleep;
        std::thread _thread;
        QThread _qthread;
        std::unique_ptr<QOpenGLContext> _ctx;
        std::mutex _mutex;

        std::queue<std::function<void()>> _tasks;
        std::map<size_t,std::shared_ptr<IGlRenderer>> _renderers;
        size_t _rendererId;

        void run();

        // Legacy
        QSurface* _surfacePtr;

        void pMakeCurrent(QSurface* surface);

    public:
        GlContext();
        ~GlContext();
        void create();
        void setFps(size_t fps);
        void destroy();
        void makeCurrent(QSurface* surface);
        size_t add(std::shared_ptr<IGlRenderer> renderer);
    };
}
#endif
