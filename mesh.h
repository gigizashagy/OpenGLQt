#ifndef MESH_H
#define MESH_H

#include <QVector2D>
#include <QVector3D>
#include <QVector>

struct VertexData
{
    VertexData(const QVector3D &pos, const QVector2D &t, const QVector3D &n)
        : position(pos), texcoord(t), normal(n)
    {}
    QVector3D position;
    QVector2D texcoord;
    QVector3D normal;
};

struct Mesh
{
public:
    Mesh(const QVector<VertexData> &vertexdata, const QVector<unsigned int> &indexdata);
    Mesh(const Mesh &other);

    QVector<VertexData> m_vertexdata;
    QVector<unsigned int> m_indexdata;
};

#endif // MESH_H
