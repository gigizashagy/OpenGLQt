#ifndef CAMERA3D_H
#define CAMERA3D_H

#include "transformationobject.h"
#include <QQuaternion>
#include <QVector3D>
#include <QMatrix4x4>



class Camera : public TransformationObject
{
public:
    Camera(float aspect, float fov, float nclip = 0.1f, float fclip = 100.f);
    ~Camera();
    // TransformationObject interface

    void rotate(const QQuaternion &r);
    void scale(const QVector3D &vec);
    void translate(const QVector3D &vec);
    void setTransform(const QMatrix4x4 &transform);
    QMatrix4x4 transform() const;
    void setGlobalTransform(const QMatrix4x4 &g);
    QVector3D getPosition() const;

    float aspectrate() const;
    void setAspectrate(float aspectrate);

    float farclip() const;
    void setFarclip(float farclip);

    float nearclip() const;
    void setNearclip(float nearclip);

    const QMatrix4x4 &projectionMatrix() const;

    QVector3D getScale() const;

private:

    QMatrix4x4 m_projectionMatrix;
    QMatrix4x4 m_globalTransform;

    QQuaternion m_rotation;
    QVector3D m_scale;
    QVector3D m_position;
    float m_aspectrate;
    float m_fov;
    float m_farclip;
    float m_nearclip;


};

#endif // CAMERA3D_H
