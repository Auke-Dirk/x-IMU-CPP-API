#ifndef ORIENTATION_VIEW_H_
#define ORIENTATION_VIEW_H_

#include <QVector2D>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QBasicTimer>
#include <QOpenGLBuffer>
#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "ximugui/widgets/geometryengine.h"


namespace Ui {
class OrientationView;
}

class OrientationView : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OrientationView(QWidget *parent = 0);
    ~OrientationView();

    void rotation(QQuaternion& quaternion);

private:

    Ui::OrientationView *ui;

    QBasicTimer _timer;
    QOpenGLBuffer _arrayBuffer;
    QOpenGLBuffer _indexBuffer;

    QMatrix4x4 _projection;
    QOpenGLShaderProgram _program;
    GeometryEngine* _geometryEngine;
    QOpenGLTexture *_texture;
    QQuaternion _rotation;

protected:
    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;

     void initializeGL() Q_DECL_OVERRIDE;
     void resizeGL(int w, int h) Q_DECL_OVERRIDE;
     void paintGL() Q_DECL_OVERRIDE;
     void initShaders();
     void initTextures();
};

#endif // ORIENTATION_VIEW_H_
