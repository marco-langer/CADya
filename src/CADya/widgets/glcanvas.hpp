#ifndef CADYA_GLCANVAS_HPP
#define CADYA_GLCANVAS_HPP

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class GLCanvas : public QOpenGLWidget
               , protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLCanvas(QWidget* parent = nullptr);
    ~GLCanvas();
    GLCanvas(GLCanvas const &) = delete;
    GLCanvas & operator=(GLCanvas const &) = delete;

    auto sizeHint() const -> QSize override;

protected:
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    void linkAndBindProgram();

    QMatrix4x4 model_;
    QMatrix4x4 projection_;
    QMatrix4x4 view_;
    QOpenGLShaderProgram * program_{};

    int projId_{};
    int modelId_{};
    int viewId_{};

    QOpenGLVertexArrayObject vao_;
    QOpenGLBuffer vbo_;
};

#endif