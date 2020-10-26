#pragma once
#include "../lib/entity.h"
#include "glm/mat4x4.hpp"

class Camera : public Entity
{
    glm::mat4 m_ProjectionMatrix;
    glm::ivec4 m_Viewport;
    glm::vec3 m_ClearColor;

public:
    Camera();

    const glm::mat4& getProjection() const;
    void setProjection(const glm::mat4& proj);
    const glm::ivec4& getViewport() const;
    void setViewport(const glm::ivec4& vp);
    const glm::vec3& getClearColor() const;
    void setClearColor(const glm::vec3& color);

    void prepare();
};
