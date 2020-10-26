#include "../lib/shader.h"
#include "../../lib/state.h"
#include "../../lib/light.h"

std::shared_ptr<Shader> State::defaultShader = nullptr;
glm::mat4 State::projectionMatrix = glm::mat4();
glm::mat4 State::viewMatrix = glm::mat4();
glm::mat4 State::modelMatrix = glm::mat4();
std::vector<std::shared_ptr<Light>> State::lights;
glm::vec3 State::ambient = glm::vec3();