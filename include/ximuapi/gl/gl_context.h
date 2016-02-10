/*
  Copyright 2015 Auke-Dirk Pietersma
*/
#ifndef XIMUAPI_GL_GL_CONTEXT_H
#define XIMUAPI_GL_GL_CONTEXT_H

#include <thread>
#include <mutex>
#include <QOpenGLContext>
#include <memory>
#include <queue>
#include <map>
#include <ximuapi/gl/igl_renderer.h>

namespace ximu{
     /**
     * @brief The GlContext class represents a QOpenGLContext.
     *
     * All calls that need to be executed within the QOpenGLContext
     * creation Thread.
     */
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
        std::unique_ptr<QOpenGLContext> _ctx;
        std::mutex _mutex;

        std::queue<std::function<void()>> _tasks;
        std::map<size_t,std::shared_ptr<IGlRenderer>> _renderers;
        size_t _rendererId;

        void run();

        QSurface* _surfacePtr;

        void pMakeCurrent(QSurface* surface);


    public:
        /**
         * @brief Creates a new QOpenGLContext context instance.
         */
        GlContext();        
        /**
         *  @brief Destroys the GlContext object.
         **/
        ~GlContext();
        /**
         * @brief create, Attempts to create the OpenGL context with the current configuration.
         */
        void create();        
        /**
         * @brief destroy, destroys the GlContext.
         */
        void destroy();
        /**
         * @brief GlContext::makeCurrent Makes the context current in the GlContext's thread, against the given surface.
         * @param surface
         */
        void makeCurrent(QSurface* surface);
        /**
         * @brief add an IGlRenderer
         * @param renderer
         * @return reference id of the IGlRenderer added
         */
        size_t add(std::shared_ptr<IGlRenderer> renderer);
    };
}
#endif
