#include "object3d.h"
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

Object3D::Object3D()
    : m_indexBuffer(QOpenGLBuffer::IndexBuffer),
      m_texture(nullptr)
{

}

Object3D::Object3D(Mesh *mesh, const QImage &texture)
    : m_indexBuffer(QOpenGLBuffer::IndexBuffer),
      m_texture(nullptr)
{
    init(mesh, texture);
    m_transform.setToIdentity();
}

Object3D::~Object3D()
{
    releaseBuffers();
    m_transform.setToIdentity();
}

void Object3D::init(Mesh *mesh, const QImage &texture)
{
   // releaseBuffers();
    m_mesh = mesh;
    m_vertexBuffer.create();
    m_vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(m_mesh->m_vertexdata.constData(), mesh->m_vertexdata.size() * sizeof (VertexData));
   // m_vertexBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indexBuffer.bind();
    m_indexBuffer.allocate(m_mesh->m_indexdata.constData(), m_mesh->m_indexdata.size() * sizeof (GLuint));
    //m_indexBuffer.release();

    m_texture = new QOpenGLTexture(texture.mirrored());

    //m_texture->setSamples(16);
    // фильтрация текстур
//    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMinificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);

}

void Object3D::draw(QOpenGLShaderProgram *shader, QOpenGLFunctions *functions)
{
    if (!m_vertexBuffer.isCreated() || !m_indexBuffer.isCreated()) return;

    m_transform = m_globalMatrix * m_transform;
    // 0 <- index of texture for shader
    m_texture->bind(0);
    shader->setUniformValue("u_texture", 0);
    shader->setUniformValue("u_modelMatrix", m_transform);

    m_vertexBuffer.bind();

    int mem_offset = 0;
   // int attributeloc = shader->attributeLocation("a_position");
    shader->enableAttributeArray("a_position");
    shader->setAttributeBuffer("a_position", GL_FLOAT, mem_offset, 3, sizeof (VertexData));

    mem_offset += sizeof (QVector3D);
   // attributeloc = shader->attributeLocation("a_texcoord");
    shader->enableAttributeArray("a_texcoord");
    shader->setAttributeBuffer("a_texcoord", GL_FLOAT, mem_offset, 2, sizeof (VertexData));

    mem_offset += sizeof (QVector2D);
   // attributeloc = shader->attributeLocation("a_normal");
    shader->enableAttributeArray("a_normal");
    shader->setAttributeBuffer("a_normal", GL_FLOAT, mem_offset, 3, sizeof (VertexData));

    m_indexBuffer.bind();

    functions->glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);

    m_texture->release();
    m_vertexBuffer.release();
    m_indexBuffer.release();
}

void Object3D::rotate(const QQuaternion &r)
{
    m_transform.rotate(r);
}

void Object3D::scale(const QVector3D &s)
{
    m_transform.scale(s);
}

void Object3D::translate(const QVector3D &t)
{
    m_transform.translate(t);
}

void Object3D::setTransform(const QMatrix4x4 &transform)
{
    m_transform = transform;
}

QMatrix4x4 Object3D::transform() const
{
    return  m_transform;
}

QVector3D Object3D::getPosition() const
{
    return  m_transform.column(3).toVector3D();
}

void Object3D::setGlobalTransform(const QMatrix4x4 &m)
{
    m_globalMatrix = m;
}

void Object3D::releaseBuffers()
{
    if (m_vertexBuffer.isCreated())
        m_vertexBuffer.destroy();
    if (m_indexBuffer.isCreated())
        m_indexBuffer.destroy();
    if (!m_texture)
        if(m_texture->isCreated())
        {
            delete m_texture;
            m_texture = nullptr;
        }

}

