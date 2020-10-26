#pragma once
#include <memory>
#include <list>

class Entity;
class Camera;

class World
{
    std::list<std::shared_ptr<Entity>> m_Entities;
    std::list<std::shared_ptr<Camera>> m_Cameras;

public:
    void addEntity(const std::shared_ptr<Entity>& entity);
    void removeEntity(const std::shared_ptr<Entity>& entity);
    size_t getNumEntities() const;
    const std::shared_ptr<Entity>& getEntity(size_t index) const;
    std::shared_ptr<Entity>& get_entity(size_t index);
    void update(float deltaTime);
    void draw();
};