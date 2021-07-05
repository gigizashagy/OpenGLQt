#include "glwidget.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimerEvent>

#include <QDebug>
#include <QtMath>
#include <QOpenGLContext>
#include "object3d.h"
#include "groupobject3d.h"
#include "camera3d.h"
#include "primitive.h"
#include "skybox.h"

static const float rotationSpeed(0.5f);

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
//    QSurfaceFormat format;
//    format.setSamples(4);
//    format.setDepthBufferSize(24);
//    setFormat(format);

    float aspect = this->width() / (float)this->height();
    m_camera = new Camera(aspect, 60.f, 0.1f, 500.f);
    m_camera->translate(QVector3D(0.0f,0.0f, -10.0f));

    rotationVec = QVector2D(0.0f,25.0f);
    QMatrix4x4 rotMat;
    rotMat.translate(m_camera->getPosition());
    rotMat.rotate(QQuaternion::fromAxisAndAngle(QVector3D(1.f,0.f,0.f), rotationVec.y()));
    rotMat.rotate(QQuaternion::fromAxisAndAngle(QVector3D(0.f,1.f,0.f), rotationVec.x()));

    QVector3D scale = m_camera->getScale();
    m_camera->setTransform(rotMat);
    m_camera->scale(scale);
}

GLWidget::~GLWidget()
{
    delete m_camera;
    for(int i = 0; i < m_objects.size(); ++i)
        delete m_objects[i];

    m_objects.clear();
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
        m_mousePosition = QVector2D(event->localPos());
    event->accept();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton) return;
    // вычисление смещения мыши относительно окна приложения
    QVector2D deltaPos = QVector2D(event->localPos()) - m_mousePosition;
    m_mousePosition = QVector2D(event->localPos());

    rotationVec += deltaPos * rotationSpeed;

    QMatrix4x4 rotMat;
    rotMat.translate(m_camera->getPosition());
    rotMat.rotate(QQuaternion::fromAxisAndAngle(QVector3D(1.f,0.f,0.f), rotationVec.y()));
    rotMat.rotate(QQuaternion::fromAxisAndAngle(QVector3D(0.f,1.f,0.f), rotationVec.x()));

    QVector3D scale = m_camera->getScale();
    m_camera->setTransform(rotMat);
    m_camera->scale(scale);

    update();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{

    if (event->delta() > 0)
        //m_camera->translate(QVector3D(0.f,0.f,0.25f));
        m_camera->scale(QVector3D(1.15f,1.15f, 1.15f));
       // m_camera->translate(m_camera->transform().column(2).toVector3D());
    else
        //m_camera->translate(QVector3D(0.f,0.f,-0.25f));
        m_camera->scale(QVector3D(0.85f,0.85f, 0.85f));
       // m_camera->translate(-m_camera->transform().column(2).toVector3D());

    update();
}

void GLWidget::initializeGL()
{
    qDebug() << "initializeGL";
    glClearColor(0.1f,0.1f,0.1f,1.f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    Q_ASSERT_X(initShaders(),"ALARM","shaser initialization fail");

    m_objects.append(new Object3D(Primitive::Cube(2.f),QImage(":/Textures/smile.jpeg")));
    m_objects.last()->translate(QVector3D(0.f,4.0f,0.0f));
    m_objects.last()->rotate(QQuaternion::fromAxisAndAngle(0,0,1,180));

    m_objects.append(new Object3D(Primitive::Plane(10.f), QImage(":/Textures/grid.png")));
    m_objects.last()->translate(QVector3D(0.f,-8.0f,0.0f));

    m_skybox = new SkyBox(QImage(":/Textures/Daylight Box UV.png"));

}

void GLWidget::resizeGL(int w, int h)
{
    m_camera->setAspectrate(w / (float)h);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // забиндить текущий шейдер для opgl
    m_shaderskybox.bind();
    m_shaderskybox.setUniformValue("u_projectionMatrix", m_camera->projectionMatrix());
    m_shaderskybox.setUniformValue("u_viewMatrix", m_camera->transform());
    m_skybox->draw(&m_shaderskybox, context()->functions());
    m_shaderskybox.release();

    m_shader.bind();
    m_shader.setUniformValue("u_projectionMatrix", m_camera->projectionMatrix());
    m_shader.setUniformValue("u_viewMatrix", m_camera->transform());

    m_shader.setUniformValue("u_lightPosition", QVector4D(0.f,0.f,0.f,1.f));
    m_shader.setUniformValue("u_lightPower", 1.0f);

    for (auto obj : m_objects)
        obj->draw(&m_shader, context()->functions());
    // когда шейдер все отрисовал освободить для другого
    m_shader.release();
}

bool GLWidget::initShaders()
{
    if (!m_shader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vtxshader.vsh"))
        return false;
    if (!m_shader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh"))
        return false;
    if (!m_shader.link())
        return false;

    if (!m_shaderskybox.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/skybox.vsh"))
        return false;
    if (!m_shaderskybox.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/skybox.fsh"))
        return false;
    if (!m_shaderskybox.link())
        return false;
    return true;
}
