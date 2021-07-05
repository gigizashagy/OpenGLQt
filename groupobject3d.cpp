#include "groupobject3d.h"
#include <QMatrix4x4>


GroupObject3d::GroupObject3d()
    : m_scale(1.0f,1.0f,1.0f)
{

}

void GroupObject3d::rotate(const QQuaternion &r)
{
    m_rotate *= r;
}

void GroupObject3d::scale(const QVector3D &s)
{
    m_scale = s;
}

void GroupObject3d::translate(const QVector3D &t)
{
    m_translate += t;
}

void GroupObject3d::setGlobalTransform(const QMatrix4x4 &m)
{
    m_globalMatrix = m;
}

void GroupObject3d::draw(QOpenGLShaderProgram *shader, QOpenGLFunctions *functions)
{
    QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(m_translate);
    localMatrix.rotate(m_rotate);
    localMatrix.scale(m_scale);
    localMatrix = m_globalMatrix * localMatrix;
    for (auto obj : m_objects)
    {
        obj->setGlobalTransform(localMatrix);
       // obj->draw(shader, functions);
    }
}

void GroupObject3d::addObject(TransformationObject *object)
{
    m_objects.append(object);
}
