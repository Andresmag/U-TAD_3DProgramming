#include "../lib/shader.h"
#include "../../lib/state.h"

std::shared_ptr<Shader> State::defaultShader = nullptr;
glm::mat4 State::projectionMatrix = glm::mat4();
glm::mat4 State::viewMatrix = glm::mat4();
glm::mat4 State::modelMatrix = glm::mat4();