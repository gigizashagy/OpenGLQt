#ifndef GROUPOBJECT3D_H
#define GROUPOBJECT3D_H
#include "transformationobject.h"
#include <QVector>
#include <QQuaternion>
#include <QMatrix4x4>

class GroupObject3d : public TransformationObject
{
public:
    GroupObject3d();

    // TransformationObject interface
public:
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const QVector3D &s);
    void setGlobalTransform(const QMatrix4x4 &m);
    void draw(QOpenGLShaderProgram *shader, QOpenGLFunctions *functions);

    void addObject(TransformationObject *object);
private:
    QQuaternion m_rotate;
    QVector3D m_translate;
    QVector3D m_scale;
    QMatrix4x4 m_globalMatrix;

    QVector<TransformationObject *> m_objects;
};

#endif // GROUPOBJECT3D_H
