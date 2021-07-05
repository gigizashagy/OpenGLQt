#include "mesh.h"


Mesh::Mesh(const QVector<VertexData> &vertexdata, const QVector<unsigned int> &indexdata)
    : m_vertexdata(vertexdata),
      m_indexdata(indexdata)
{}

Mesh::Mesh(const Mesh &other)
    : m_vertexdata(other.m_vertexdata),
      m_indexdata(other.m_indexdata)
{}
