#include "glcanvas.hpp"

#include <kernel/math.hpp>

#include <cassert>
#include <cmath>

/**
 * A test to display a simple circle. TLDR: it does not work.
 */

namespace {

constexpr int windowDefaultWidth = 1076;
constexpr int windowDefaultHeight = 768;

constexpr int vertexCountPerCicle = 32;

const char * circleVertexShader = R"(
    #version 330 core
    layout(location = 0) in vec2 aPos;

    uniform mat4 model;
    uniform mat4 projection;
    uniform mat4 view;

    void main()
    {
      vec4 result = projection * view * model * vec4(aPos.x, aPos.y, 0.0f, 1.0f);
      gl_Position = result;
    }
)";
const char * circleFragmentShader = R"(
    #version 330 core

    out vec4 FragColor;

    void main()
    {
      FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
)";

} // namespace

GLCanvas::GLCanvas(QWidget * parent)
    : QOpenGLWidget(parent)
{}

GLCanvas::~GLCanvas()
{
    if (program_ == nullptr)
    {
        return;
    }

    makeCurrent();

    vbo_.destroy();
    vao_.destroy();

    doneCurrent();
}

auto GLCanvas::sizeHint() const -> QSize
{
    return QSize{windowDefaultWidth, windowDefaultHeight};
}

void GLCanvas::mousePressEvent(QMouseEvent * /* event */)
{
    //TODO
}

void GLCanvas::mouseMoveEvent(QMouseEvent * /* event */)
{
    //TODO
}

void GLCanvas::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    view_.lookAt(
        QVector3D(4, 1, 0),
        QVector3D(0, 0, 0),
        QVector3D(0, 1, 0)
    );

    linkAndBindProgram();
}

void GLCanvas::paintGL()
{
    if (program_ == nullptr)
    {
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program_->bind();
    auto const vaoBinder = QOpenGLVertexArrayObject::Binder{&vao_};

    model_.setToIdentity();
    model_.translate(windowDefaultWidth/2, windowDefaultHeight/2, 2.0);
    model_.scale(10.0);

    program_->setUniformValue(projId_, projection_);
    program_->setUniformValue(modelId_, model_);

    glDrawElements(GL_TRIANGLE_FAN, 2 * vertexCountPerCicle, GL_UNSIGNED_INT, nullptr);

    program_->release();
}

void GLCanvas::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    auto const aspectRation = static_cast<float>(width) / height;
    projection_.setToIdentity();
    projection_.ortho(-aspectRation, aspectRation, -1.0f, 1.0f, -1.0f, 1.0f);
}

void GLCanvas::linkAndBindProgram()
{
    program_ = new QOpenGLShaderProgram(this);
    auto success = program_->addShaderFromSourceCode(
        QOpenGLShader::Vertex,
        circleVertexShader
    );
    assert(success);
    success = program_->addShaderFromSourceCode(
        QOpenGLShader::Fragment,
        circleFragmentShader
    );
    assert(success);

    program_->bindAttributeLocation("aPos", 0);
    success = program_->link();
    assert(success);

    glViewport(0, 0, windowDefaultWidth, windowDefaultWidth);
    auto const aspectRatio = static_cast<float>(windowDefaultWidth) / windowDefaultWidth;
    projection_.ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);

    projId_ = program_->uniformLocation("projection");
    modelId_ = program_->uniformLocation("model");
    viewId_ = program_->uniformLocation("view");

    program_->bind();

    vao_.create();
    vbo_.create();

    auto vertices = std::vector<float>{};
    vertices.reserve(2 * vertexCountPerCicle);

    vertices.push_back(0.0f);
    vertices.push_back(0.0f);

    constexpr auto degreesBetweenVertices = 360.0f / (vertexCountPerCicle - 6);

    for (auto i = 1; i < vertexCountPerCicle; ++i)
    {
        auto const angle_rad = cy::degrees_to_radians(
            static_cast<float>(i) * degreesBetweenVertices
        );
        vertices.push_back(std::cos(angle_rad));
        vertices.push_back(std::sin(angle_rad));
    }

    auto const vaoBinder = QOpenGLVertexArrayObject::Binder{&vao_};

    vbo_.bind();
    vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo_.allocate(
        vertices.data(),
        static_cast<int>(vertices.size() * sizeof(float))
    );

    auto const position = program_->attributeLocation("aPos");
    program_->enableAttributeArray(position);
    program_->setAttributeBuffer(position, GL_FLOAT, 0, 2, 0);

    vbo_.release();
    program_->release();
}