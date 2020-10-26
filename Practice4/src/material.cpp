#include "../lib/texture.h"
#include "../lib/shader.h"
#include "../lib/state.h"
#include "../lib/material.h"
#include "../lib/light.h"

Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader)
    : m_Texture(tex)
    , m_Shader(shader)
    , m_Color(0.f, 0.f, 0.f, 0.f)
    , m_Shininess(0)
    , m_ambient(0.f, 0.f, 0.f)
    , m_diffuse(0.f, 0.f, 0.f)
    , m_specular(0.f, 0.f, 0.f)
{
}

const std::shared_ptr<Shader>& Material::getShader() const
{
    if (m_Shader)
    {
        return m_Shader;
    }

    return State::defaultShader;
}

std::shared_ptr<Shader>& Material::getShader()
{
    if (m_Shader)
    {
        return m_Shader;
    }

    return State::defaultShader;
}

void Material::setShader(const std::shared_ptr<Shader>& shader)
{
    m_Shader = shader;
}

const std::shared_ptr<Texture>& Material::getTexture() const
{
    return m_Texture;
}

void Material::setTexture(const std::shared_ptr<Texture>& tex)
{
    m_Texture = tex;
}

const glm::vec4& Material::getColor() const
{
    return m_Color;
}

void Material::setColor(const glm::vec4& color)
{
    m_Color = color;
}

uint8_t Material::getShininess() const
{
    return m_Shininess;
}

void Material::setShininess(uint8_t shininess)
{
    m_Shininess = shininess;
}

glm::vec3 Material::getAmbient() const
{
    return m_ambient;
}

void Material::setAmbient(const glm::vec3& ambient)
{
    m_ambient = ambient;
}

glm::vec3 Material::getDiffuse() const
{
    return m_diffuse;
}

void Material::setDiffuse(const glm::vec3& diffuse)
{
    m_diffuse = diffuse;
}

glm::vec3 Material::getSpecular() const
{
    return m_specular;
}

void Material::setSpecular(const glm::vec3& specular)
{
    m_specular = specular;
}

void Material::prepare()
{
    getShader()->use();
    m_Texture->bind();
    m_Shader->setInt(m_Shader->getLocation("texSampler"), 0);
    m_Shader->setMatrix(m_Shader->getLocation("mv_matrix"), State::viewMatrix * State::modelMatrix);
    m_Shader->setMatrix(m_Shader->getLocation("proj_matrix"), State::projectionMatrix);
    m_Shader->setMatrix(m_Shader->getLocation("norm_matrix"), transpose(inverse(State::viewMatrix * State::modelMatrix)));

    // Material data
    m_Shader->setVec4(m_Shader->getLocation("material.ambient"), glm::vec4(m_ambient.x, m_ambient.y, m_ambient.z, 0.f));
    m_Shader->setVec4(m_Shader->getLocation("material.diffuse"), glm::vec4(m_diffuse.x, m_diffuse.y, m_diffuse.z, 0.f));
    m_Shader->setVec4(m_Shader->getLocation("material.specular"), glm::vec4(m_specular.x, m_specular.y, m_specular.z, 0.f));
    m_Shader->setFloat(m_Shader->getLocation("material.shininess"), m_Shininess);

    // Light data
    m_Shader->setInt(m_Shader->getLocation("num_lights"), static_cast<int>(State::lights.size()));
    m_Shader->setVec4(m_Shader->getLocation("globalAmbient"), glm::vec4(State::ambient.x, State::ambient.y, State::ambient.z, 0.f));

    for(int idx=0; idx < State::lights.size(); idx++)
    {
        State::lights[idx]->prepare(idx, m_Shader);
    }
}
