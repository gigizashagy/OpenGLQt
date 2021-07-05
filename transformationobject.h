#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

class QQuaternion;
class QVector3D;
class QMatrix4x4;
class QOpenGLShaderProgram;
class QOpenGLFunctions;

class TransformationObject
{
public:
    virtual ~TransformationObject(){};
    virtual void rotate(const QQuaternion &r) = 0;
    virtual void translate(const QVector3D &vec) = 0;
    virtual void scale(const QVector3D &vec) = 0;
    virtual void setTransform(const QMatrix4x4 &transform) = 0;
    virtual QMatrix4x4 transform() const = 0;
    virtual QVector3D getPosition() const = 0;
    virtual void setGlobalTransform(const QMatrix4x4 &g) = 0;
};

#endif // TRANSFORMATION_H
