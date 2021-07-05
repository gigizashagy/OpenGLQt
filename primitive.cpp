#include "primitive.h"

#include "object3d.h"

Mesh *Primitive::Cube(float width)
{
    QVector<VertexData> verteses;
    QVector<unsigned int> indexes;

    verteses.append(VertexData(QVector3D(-width, width, width),  QVector2D(0.0f, 0.0f), QVector3D(0.f,0.f,1.f)));
    verteses.append(VertexData(QVector3D(width, width, width),   QVector2D(1.0f, 0.0f), QVector3D(0.f,0.f,1.f)));
    verteses.append(VertexData(QVector3D(width, -width, width),  QVector2D(1.0f, 1.0f), QVector3D(0.f,0.f,1.f)));
    verteses.append(VertexData(QVector3D(-width, -width, width), QVector2D(0.0f, 1.0f), QVector3D(0.f,0.f,1.f)));

    verteses.append(VertexData(QVector3D(-width, width, -width), QVector2D(0.0f, 0.0f), QVector3D(0.f,1.f,0.f)));
    verteses.append(VertexData(QVector3D(width, width, -width),  QVector2D(1.0f, 0.0f), QVector3D(0.f,1.f,0.f)));
    verteses.append(VertexData(QVector3D(width, width, width),   QVector2D(1.0f, 1.0f), QVector3D(0.f,1.f,0.f)));
    verteses.append(VertexData(QVector3D(-width, width, width),  QVector2D(0.0f, 1.0f), QVector3D(0.f,1.f,0.f)));

    verteses.append(VertexData(QVector3D(-width, width, -width), QVector2D(0.0f, 0.0f), QVector3D(-1.f,0.f,0.f)));
    verteses.append(VertexData(QVector3D(-width, width, width),  QVector2D(1.0f, 0.0f), QVector3D(-1.f,0.f,0.f)));
    verteses.append(VertexData(QVector3D(-width, -width, width), QVector2D(1.0f, 1.0f), QVector3D(-1.f,0.f,0.f)));
    verteses.append(VertexData(QVector3D(-width, -width, -width),QVector2D(0.0f, 1.0f), QVector3D(-1.f,0.f,0.f)));

    verteses.append(VertexData(QVector3D(-width, -width, width), QVector2D(0.0f, 0.0f), QVector3D(0.f,-1.f,0.f)));
    verteses.append(VertexData(QVector3D(width, -width, width),  QVector2D(1.0f, 0.0f), QVector3D(0.f,-1.f,0.f)));
    verteses.append(VertexData(QVector3D(width, -width, -width), QVector2D(1.0f, 1.0f), QVector3D(0.f,-1.f,0.f)));
    verteses.append(VertexData(QVector3D(-width, -width, -width),QVector2D(0.0f, 1.0f), QVector3D(0.f,-1.f,0.f)));

    verteses.append(VertexData(QVector3D(width, width, width),   QVector2D(0.0f, 0.0f), QVector3D(1.f,0.f,0.f)));
    verteses.append(VertexData(QVector3D(width, width, -width),  QVector2D(1.0f, 0.0f), QVector3D(1.f,0.f,0.f)));
    verteses.append(VertexData(QVector3D(width, -width, -width), QVector2D(1.0f, 1.0f), QVector3D(1.f,0.f,0.f)));
    verteses.append(VertexData(QVector3D(width, -width, width),  QVector2D(0.0f, 1.0f), QVector3D(1.f,0.f,0.f)));

    verteses.append(VertexData(QVector3D(width, width, -width),  QVector2D(0.0f, 0.0f), QVector3D(0.f,0.f,-1.f)));
    verteses.append(VertexData(QVector3D(-width, width, -width), QVector2D(1.0f, 0.0f), QVector3D(0.f,0.f,-1.f)));
    verteses.append(VertexData(QVector3D(-width, -width, -width), QVector2D(1.0f, 1.0f), QVector3D(0.f,0.f,-1.f)));
    verteses.append(VertexData(QVector3D(width, -width, -width),QVector2D(0.0f, 1.0f), QVector3D(0.f,0.f,-1.f)));

    for (int i = 0; i < 24; i+=4)
    {
        indexes.append(i+0);
        indexes.append(i+3);
        indexes.append(i+1);
        indexes.append(i+1);
        indexes.append(i+3);
        indexes.append(i+2);
    }

    return new Mesh(verteses, indexes);
}

Mesh *Primitive::Plane(float width)
{
    QVector<VertexData> verteses;
    QVector<unsigned int> indexes;

    verteses.append(VertexData(QVector3D(-width, 0.f, -width),QVector2D(0.0f, 0.0f), QVector3D(0.f,1.f,0.f)));
    verteses.append(VertexData(QVector3D(width, 0.f, -width), QVector2D(1.0f, 0.0f), QVector3D(0.f,1.f,0.f)));
    verteses.append(VertexData(QVector3D(width, 0.f, width),  QVector2D(1.0f, 1.0f), QVector3D(0.f,1.f,0.f)));
    verteses.append(VertexData(QVector3D(-width, 0.f, width), QVector2D(0.0f, 1.0f), QVector3D(0.f,1.f,0.f)));

    indexes.append(0);
    indexes.append(3);
    indexes.append(1);
    indexes.append(1);
    indexes.append(3);
    indexes.append(2);

    return new Mesh(verteses, indexes);
}

Mesh *Primitive::SkyBoxCube(float width)
{
    Mesh *cube = Primitive::Cube(width);
    QVector<VertexData> &verteses = cube->m_vertexdata;
    QVector<unsigned int> indexes;
    //invert normals
        for (int i = 0; i < verteses.size(); ++i)
            verteses[i].normal *= QVector3D(-1.f,-1.f,-1.f);

        for (int i = 0; i < 24; i+=4)
        {
            indexes.append(i+0);
            indexes.append(i+1);
            indexes.append(i+3);
            indexes.append(i+3);
            indexes.append(i+1);
            indexes.append(i+2);
        }
        cube->m_indexdata = indexes;
    // front
    verteses[0].texcoord = QVector2D(0.25f, 1.f/3.f);
    verteses[1].texcoord = QVector2D(0.5f, 1.f/3.f);
    verteses[2].texcoord = QVector2D(0.5f, 2.f/3.f);
    verteses[3].texcoord = QVector2D(0.25f, 2.f/3.f);
    // top
    verteses[4].texcoord = QVector2D(0.25f, 0.f);
    verteses[5].texcoord = QVector2D(0.5f, 0.f);
    verteses[6].texcoord = QVector2D(0.5f, 1.f/3.f);
    verteses[7].texcoord = QVector2D(0.25f, 1.f/3.f);
    //left
    verteses[8].texcoord = QVector2D(0.f, 1.f/3.f);
    verteses[9].texcoord = QVector2D(0.25f, 1.f/3.f);
    verteses[10].texcoord = QVector2D(0.25f, 2.f/3.f);
    verteses[11].texcoord = QVector2D(0.f, 2.f/3.f);
    //bottom
    verteses[12].texcoord = QVector2D(0.25f, 2.f/3.f);
    verteses[13].texcoord = QVector2D(0.5f, 2.f/3.f);
    verteses[14].texcoord = QVector2D(0.5f, 1.f);
    verteses[15].texcoord = QVector2D(0.25f, 1.f);
    //right
    verteses[16].texcoord = QVector2D(0.5f, 1.f/3.f);
    verteses[17].texcoord = QVector2D(0.75f, 1.f/3.f);
    verteses[18].texcoord = QVector2D(0.75f, 2.f/3.f);
    verteses[19].texcoord = QVector2D(0.5f, 2.f/3.f);
    //back
    verteses[20].texcoord = QVector2D(0.75f, 1.f/3.f);
    verteses[21].texcoord = QVector2D(1.f, 1.f/3.f);
    verteses[22].texcoord = QVector2D(1.f, 2.f/3.f);
    verteses[23].texcoord = QVector2D(0.75f, 2.f/3.f);


    return cube;
}
