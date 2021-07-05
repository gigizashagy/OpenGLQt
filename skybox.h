#ifndef SKYBOX_H
#define SKYBOX_H

#include "transformationobject.h"

class Object3D;
class QImage;

class SkyBox : public TransformationObject
{
public:
    SkyBox(const QImage &texture);
    ~SkyBox();
    // TransformationObject interface
public:
    void draw(QOpenGLShaderProgram *shader, QOpenGLFunctions *functions);
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &vec);
    void scale(const QVector3D &vec);
    void setTransform(const QMatrix4x4 &transform);
    QMatrix4x4 transform() const;
    QVector3D getPosition() const;
    void setGlobalTransform(const QMatrix4x4 &g);
private:
    Object3D *m_cube;
};

#endif // SKYBOX_H
