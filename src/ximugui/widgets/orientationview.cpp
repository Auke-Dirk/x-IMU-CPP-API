#include "ximugui/widgets/orientationview.h"
#include "ui_orientationview.h"
#include <QFile>
#include <iostream>
#include <QThread>

OrientationView::OrientationView(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::OrientationView),
    _texture(0),
    _geometryEngine(0),
    _rotation(1.0,0,0,0),
    _axis(AxisSystem::XIMU)
{
    ui->setupUi(this);
    connect(ui->radioButton_opengl,&QRadioButton::toggled,this,&OrientationView::onAxisSystemChanged);
}

OrientationView::~OrientationView()
{
    delete ui;
}

void OrientationView::onAxisSystemChanged()
{
    bool opengl = ui->radioButton_opengl->isChecked();
    bool ximu = ui->radioButton_ximu->isChecked();

    _axis = opengl ? AxisSystem::OPEGNL : AxisSystem::XIMU;
    _changeTextures = true;
}

/*
 * OpenGL overload section
 */
void OrientationView::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    initShaders();
    initTextures();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);



     _geometryEngine = new GeometryEngine;
     _timer.start(12, this);
}

void OrientationView::timerEvent(QTimerEvent *)
{
    update();
}

void OrientationView::registerThread(QThread* thread)
{
   _thread = thread;
   connect(thread,&QThread::objectNameChanged,this,&OrientationView::run);
}

void OrientationView::run(const QString &name)
{
    while(_thread)
    {        
        paintGL();
        _thread->msleep(1000);
    }
}

void OrientationView::paintGL(){

    if (_changeTextures)
    {
        initTextures();
        _changeTextures = false;
    }

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _texture->bind();

    // Calculate model view transformation
    //_rotation *= QQuaternion(0,.1,.2,.1).normalized();
    _rotation.normalize();

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(_rotation);

    // Set modelview-projection matrix
    _program.setUniformValue("mvp_matrix", _projection * matrix);

    // Use texture unit 0 which contains cube.png
    _program.setUniformValue("texture", 0);

    // Draw cube geometry
    _geometryEngine->drawCubeGeometry(&_program);
}

void OrientationView::resizeGL(int w, int h){
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    _projection.setToIdentity();
    _projection.perspective(fov, aspect, zNear, zFar);
}

/*
 *
*/

void OrientationView::initShaders(){

    if (!_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader.glsl"))
        return;

    if (!_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader.glsl"))
        return;

    if (!_program.link())
        return;
    if (!_program.bind())
        return;
}

void OrientationView::initTextures(){

    //:/images/cube_faces_ximu.png

    if (_axis == AxisSystem::OPEGNL)
        _texture = new QOpenGLTexture(QImage(":/images/cube_faces.png"));
    else
        _texture = new QOpenGLTexture(QImage(":/images/cube_faces_ximu.png"));


    _texture->setMinificationFilter(QOpenGLTexture::Nearest);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    _texture->setWrapMode(QOpenGLTexture::Repeat);
}
void OrientationView::rotation(QQuaternion& quaternion)
{
    _rotation = quaternion;
}

 void OrientationView::onNewRotation(const ximu::QuaternionData& q)
 {
    _rotation = QQuaternion(q.w(),-q.x(), -q.z(),q.y());
 }


