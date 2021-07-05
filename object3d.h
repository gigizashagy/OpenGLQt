#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include <QImage>
#include "transformationobject.h"
#include "mesh.h"

class QOpenGLTexture;
class QOpenGLFunctions;
class QOpenGLShaderProgram;


class Object3D : public TransformationObject
{
public:
    Object3D();
    Object3D(Mesh *mesh, const QImage &texture);
    ~Object3D();
    void init(Mesh *mesh, const QImage &texture);
    // TransformationObject interface
    void draw(QOpenGLShaderProgram *shader, QOpenGLFunctions *functions);
    void rotate(const QQuaternion &r);
    void scale(const QVector3D &s);
    void translate (const QVector3D &t);
    void setTransform(const QMatrix4x4 &transform);
    QMatrix4x4 transform() const;
    QVector3D getPosition() const;
    void setGlobalTransform(const QMatrix4x4 &m);
private:
    void releaseBuffers();
    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_indexBuffer;
    QOpenGLTexture *m_texture;

    QMatrix4x4 m_transform;
    QMatrix4x4 m_globalMatrix;
    Mesh *m_mesh;

    // TransformationObject interface
public:

};

#endif // OBJECT3D_H
