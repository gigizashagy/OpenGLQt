#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QtMath>


class Object3D;
class TransformationObject;
class GroupObject3d;
class Camera;
class SkyBox;




class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

    // QOpenGLWidget interface
protected:

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

    bool initShaders();
    void initGrid(float size);

private:
    Camera *m_camera;
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_shader;
    QOpenGLShaderProgram m_shaderskybox;

    QVector2D m_mousePosition;
    QVector<Object3D *> m_objects;
    SkyBox *m_skybox;

    QVector2D rotationVec;
    // QWidget interface
protected:

};
#endif // WIDGET_H
