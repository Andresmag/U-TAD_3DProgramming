#include "../lib/light.h"
#include "../lib/shader.h"
#include <string>

Light::Type Light::getType() const
{
    return m_LightType;
}

void Light::setType(Type type)
{
    m_LightType = type;
}

const glm::vec3& Light::getColor() const
{
    return m_Color;
}

void Light::setColor(const glm::vec3& color)
{
    m_Color = color;
}

float Light::getLinearAttenuation() const
{
    return m_LinearAttenuation;
}

void Light::setLinearAttenuation(float att)
{
    m_LinearAttenuation = att;
}

void Light::prepare(int index, std::shared_ptr<Shader>& shader) const
{
    std::string lightPosDir = "lights[" + std::to_string(index) + "].posdir";
    std::string lightAmbient = "lights[" + std::to_string(index) + "].ambient";
    std::string lightDiffuse = "lights[" + std::to_string(index) + "].diffuse";
    std::string lightSpecular = "lights[" + std::to_string(index) + "].specular";
    shader->setVec3(shader->getLocation(lightPosDir.c_str()), m_Position);
    shader->setVec4(shader->getLocation(lightAmbient.c_str()), glm::vec4(m_ambient.x, m_ambient.y, m_ambient.z, 0.f));
    shader->setVec4(shader->getLocation(lightDiffuse.c_str()), glm::vec4(m_diffuse.x, m_diffuse.y, m_diffuse.z, 0.f));
    shader->setVec4(shader->getLocation(lightSpecular.c_str()), glm::vec4(m_specular.x, m_specular.y, m_specular.z, 0.f));

    if (m_LightType == Type::POINT)
    {
        std::string lightLinearAtt = "lights[" + std::to_string(index) + "].linearAtt";
        shader->setFloat(shader->getLocation(lightLinearAtt.c_str()), m_LinearAttenuation);
    }
}
