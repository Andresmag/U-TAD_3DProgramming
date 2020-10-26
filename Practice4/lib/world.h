#pragma once
#include <memory>
#include <list>
#include "glm/detail/type_vec3.hpp"


class Entity;
class Camera;
class Light;

class World
{
    std::list<std::shared_ptr<Entity>> m_Entities;
    std::list<std::shared_ptr<Camera>> m_Cameras;
    std::list<std::shared_ptr<Light>> m_Lights;

    glm::vec3 m_Ambient;

public:
    void addEntity(const std::shared_ptr<Entity>& entity);
    void removeEntity(const std::shared_ptr<Entity>& entity);
    size_t getNumEntities() const;
    const std::shared_ptr<Entity>& getEntity(size_t index) const;
    std::shared_ptr<Entity>& get_entity(size_t index);
    const glm::vec3& getAmbient() const;
    void setAmbient(const glm::vec3& ambient);
    void update(float deltaTime);
    void draw();
};