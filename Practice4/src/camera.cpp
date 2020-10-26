#include "../lib/camera.h"
#include "../lib/state.h"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "GL/glew.h"

Camera::Camera()
    : m_ProjectionMatrix(glm::mat4())
    , m_Viewport(glm::ivec4())
    , m_ClearColor(glm::vec3(0.6, 0.6, 0.6))
{
}

const glm::mat4& Camera::getProjection() const
{
    return m_ProjectionMatrix;
}

void Camera::setProjection(const glm::mat4& proj)
{
    m_ProjectionMatrix = proj;
}

const glm::ivec4& Camera::getViewport() const
{
    return m_Viewport;
}

void Camera::setViewport(const glm::ivec4& vp)
{
    m_Viewport = vp;
}

const glm::vec3& Camera::getClearColor() const
{
    return m_ClearColor;
}

void Camera::setClearColor(const glm::vec3& color)
{
    m_ClearColor = color;
}

void Camera::prepare()
{
    State::projectionMatrix = getProjection();

    State::viewMatrix = glm::translate<float>(glm::mat4(), -getPosition());
    State::viewMatrix = glm::rotate<float>(State::viewMatrix, -glm::radians(getRotation().x), glm::vec3(1, 0, 0));
    State::viewMatrix = glm::rotate<float>(State::viewMatrix, -glm::radians(getRotation().y), glm::vec3(0, 1, 0));
    State::viewMatrix = glm::rotate<float>(State::viewMatrix, -glm::radians(getRotation().z), glm::vec3(0, 0, 1));

    glViewport(m_Viewport.x, m_Viewport.y, m_Viewport.z, m_Viewport.w);
    glScissor(m_Viewport.x, m_Viewport.y, m_Viewport.z, m_Viewport.w);

    // Clean color and depth buffers
    glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
}
