#include "../lib/world.h"
#include "../lib/camera.h"
#include "../lib/light.h"
#include "../lib/state.h"

void World::addEntity(const std::shared_ptr<Entity>& entity)
{
    m_Entities.push_back(entity);

    std::shared_ptr<Camera> cam = std::dynamic_pointer_cast<Camera>(entity);
    if (cam)
    {
        m_Cameras.push_back(cam);
    }

    std::shared_ptr<Light> light = std::dynamic_pointer_cast<Light>(entity);
    if (light)
    {
        m_Lights.push_back(light);
    }
}

void World::removeEntity(const std::shared_ptr<Entity>& entity)
{
    m_Entities.remove(entity);

    std::shared_ptr<Camera> cam = std::dynamic_pointer_cast<Camera>(entity);
    if (cam)
    {
        m_Cameras.remove(cam);
    }

    std::shared_ptr<Light> light = std::dynamic_pointer_cast<Light>(entity);
    if (light)
    {
        m_Lights.remove(light);
    }
}

size_t World::getNumEntities() const
{
    return m_Entities.size();
}

const std::shared_ptr<Entity>& World::getEntity(size_t index) const
{
    unsigned int idx = 0;
    for (auto it = m_Entities.begin(); it != m_Entities.end(); ++it)
    {
        if (idx == index)
        {
            return *it;
        }
        idx++;
    }
}

std::shared_ptr<Entity>& World::get_entity(size_t index)
{
    unsigned int idx = 0;
    for (auto it = m_Entities.begin(); it != m_Entities.end(); ++it)
    {
        if (idx == index)
        {
            return *it;
        }
        idx++;
    }
}

const glm::vec3& World::getAmbient() const
{
    return m_Ambient;
}

void World::setAmbient(const glm::vec3& ambient)
{
    m_Ambient = ambient;
}

void World::update(float deltaTime)
{
    for(auto& entity : m_Entities)
    {
        entity->update(deltaTime);
    }
}

void World::draw()
{
    State::lights.clear();
    for (auto& light : m_Lights)
    {
        State::lights.push_back(light);
    }
    State::ambient = m_Ambient;

    for (auto& camera : m_Cameras)
    {
        camera->prepare();
    }

    for (auto& entity : m_Entities)
    {
        entity->draw();
    }
}
