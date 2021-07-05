#include "camera3d.h"
#include <QOpenGLShaderProgram>

Camera::Camera(float aspect, float fov, float nclip, float fclip)
    : m_aspectrate(aspect),
      m_fov(fov),
      m_farclip(fclip),
      m_nearclip(nclip)
{
    m_scale = QVector3D(1.0f,1.0f,1.0f);
    m_globalTransform.setToIdentity();
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(m_fov, m_aspectrate, m_nearclip, m_farclip);
}

Camera::~Camera()
{

}

void Camera::rotate(const QQuaternion &r)
{
    m_rotation *= r;

}

void Camera::translate(const QVector3D &vec)
{

    m_position += vec;
}

void Camera::setTransform(const QMatrix4x4 &transform)
{
    m_scale = QVector3D(transform.column(0).length(),
                        transform.column(1).length(),
                        transform.column(2).length());
    m_rotation = QQuaternion::fromRotationMatrix(transform.normalMatrix());
    m_position = transform.column(3).toVector3D();

}

QMatrix4x4 Camera::transform() const
{
    QMatrix4x4 mat;
    mat.translate(m_position);
    mat.rotate(m_rotation);
    mat.scale(m_scale);
    return mat;
}

void Camera::scale(const QVector3D &vec)
{
    m_scale *= vec;
}

void Camera::setGlobalTransform(const QMatrix4x4 &g)
{
    m_globalTransform = g;
}

QVector3D Camera::getPosition() const
{
    return m_position;
}


float Camera::aspectrate() const
{
    return m_aspectrate;
}

void Camera::setAspectrate(float aspectrate)
{
    m_aspectrate = aspectrate;
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(m_fov, m_aspectrate, m_nearclip, m_farclip);
}

float Camera::farclip() const
{
    return m_farclip;
}

void Camera::setFarclip(float farclip)
{
    m_farclip = farclip;
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(m_fov, m_aspectrate, m_nearclip, m_farclip);
}

float Camera::nearclip() const
{
    return m_nearclip;
}

void Camera::setNearclip(float nearclip)
{
    m_nearclip = nearclip;
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(m_fov, m_aspectrate, m_nearclip, m_farclip);
}

const QMatrix4x4 &Camera::projectionMatrix() const
{
    return m_projectionMatrix;
}

QVector3D Camera::getScale() const
{
    return m_scale;
}
