#include "../lib/entity.h"

Entity::Entity()
    : m_Position(glm::vec3(0, 0, 0))
    , m_Rotation(glm::vec3(0, 0, 0))
    , m_Scale(glm::vec3(1, 1, 1))
{
}

const glm::vec3& Entity::getPosition() const
{
    return m_Position;
}

void Entity::setPosition(const glm::vec3& pos)
{
    m_Position = pos;
}

const glm::vec3& Entity::getRotation() const
{
    return m_Rotation;
}

void Entity::setRotation(const glm::vec3& rot)
{
    m_Rotation = rot;
}

const glm::vec3& Entity::getScale() const
{
    return m_Scale;
}

void Entity::setScale(const glm::vec3& scale)
{
    m_Scale = scale;
}
