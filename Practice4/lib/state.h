#pragma once
#include <memory>
#include <vector>
#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_vec3.hpp"

class Shader;
class Light;

class State
{
public:
    static std::shared_ptr<Shader> defaultShader;
    static glm::mat4 projectionMatrix;
    static glm::mat4 viewMatrix;
    static glm::mat4 modelMatrix;
    static std::vector<std::shared_ptr<Light>> lights;
    static glm::vec3 ambient;
};
