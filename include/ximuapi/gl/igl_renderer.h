#ifndef XIMU_GL_GL_RENDERER_H_
#define XIMU_GL_GL_RENDERER_H_

#include <QOpenGLContext>
#include <memory>

namespace ximu {

    class IGlRenderer
    {
    public:
        virtual void render() = 0;
        virtual void initializeGL(std::unique_ptr<QOpenGLContext>& ctx) = 0;
    };

}

#endif
