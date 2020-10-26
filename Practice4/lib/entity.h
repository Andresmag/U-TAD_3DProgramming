#pragma once
#include "glm/detail/type_vec3.hpp"

class Entity
{
protected:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;

public:
    Entity();
    virtual ~Entity() {}
    const glm::vec3& getPosition() const;
    void setPosition(const glm::vec3& pos);
    const glm::vec3& getRotation() const;
    void setRotation(const glm::vec3& rot);
    const glm::vec3& getScale() const;
    void setScale(const glm::vec3& scale);
    void move(const glm::vec3& vec);
    virtual void update(float deltaTime) {}
    virtual void draw() {}
};
