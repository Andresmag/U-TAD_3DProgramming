#include "../lib/mesh.h"
#include "../lib/model.h"
#include "../lib/state.h"
#include "../lib/glm/gtc/quaternion.hpp"
#include "../lib/glm/gtc/matrix_transform.hpp"

Model::Model(const std::shared_ptr<Mesh>& mesh)
    : m_Mesh(mesh)
    , m_UpdateFunc(nullptr)
{
}

void Model::setCallbackFunc(CallbackFunc func)
{
    m_UpdateFunc = func;
}

void Model::update(float deltaTime)
{
    if (m_UpdateFunc != nullptr)
    {
        m_UpdateFunc(*this, deltaTime);
    }
}

void Model::draw()
{
    // Set modelMatrix
    State::modelMatrix = glm::translate<float>(glm::mat4(), getPosition());
    State::modelMatrix = glm::rotate<float>(State::modelMatrix, glm::radians(getRotation().x), glm::vec3(1, 0, 0));
    State::modelMatrix = glm::rotate<float>(State::modelMatrix, glm::radians(getRotation().y), glm::vec3(0, 1, 0));
    State::modelMatrix = glm::rotate<float>(State::modelMatrix, glm::radians(getRotation().z), glm::vec3(0, 0, 1));
    State::modelMatrix = glm::scale<float>(State::modelMatrix, getScale());

    m_Mesh->draw();
}
