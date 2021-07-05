#include "skybox.h"
#include <QMatrix4x4>
#include <QVector3D>
#include "object3d.h"
#include "primitive.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>


SkyBox::SkyBox(const QImage &texture)
{
    m_cube = new Object3D(Primitive::SkyBoxCube(250.f), texture.mirrored());
}

SkyBox::~SkyBox()
{
    delete m_cube;
}

void SkyBox::draw(QOpenGLShaderProgram *shader, QOpenGLFunctions *functions)
{
    m_cube->draw(shader, functions);
}

void SkyBox::rotate(const QQuaternion &r)
{
    (void)r;
}

void SkyBox::translate(const QVector3D &vec)
{
    (void)vec;
}

void SkyBox::scale(const QVector3D &vec)
{
    (void)vec;
}

void SkyBox::setTransform(const QMatrix4x4 &transform)
{
    (void)transform;
}

QMatrix4x4 SkyBox::transform() const
{
    return QMatrix4x4();
}

QVector3D SkyBox::getPosition() const
{
    return QVector3D();
}

void SkyBox::setGlobalTransform(const QMatrix4x4 &g)
{
    (void)&g;
}
