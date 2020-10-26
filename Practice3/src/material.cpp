#include "../lib/texture.h"
#include "../lib/shader.h"
#include "../lib/state.h"
#include "../lib/material.h"

Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader)
    : m_Texture(tex)
    , m_Shader(shader)
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

void Material::prepare()
{
    getShader()->use();
    m_Texture->bind();
    m_Shader->setInt(m_Shader->getLocation("texSampler"), 0);
    m_Shader->setMatrix(m_Shader->getLocation("mvp"), State::projectionMatrix * State::viewMatrix * State::modelMatrix);
}
