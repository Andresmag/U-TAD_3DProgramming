#pragma once
#include "entity.h"
#include <memory>

class Shader;

class Light : public Entity
{
public:
    enum class Type
    {
        NONE,
        DIRECTIONAL,
        POINT
    };

private:
    Type m_LightType;
    glm::vec3 m_Color;
    float m_LinearAttenuation;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

public:
    Light()
        : m_LightType(Type::NONE)
        , m_Color(0.f, 0.f, 0.f)
        , m_LinearAttenuation(0.f)
    {}

    Light(Type lightType, glm::vec3 color, float linAtt)
        : m_LightType(lightType)
        , m_Color(color)
        , m_LinearAttenuation(linAtt)
    {}

    Type getType() const;
    void setType(Type type);
    const glm::vec3& getColor() const;
    void setColor(const glm::vec3& color);
    float getLinearAttenuation() const;
    void setLinearAttenuation(float att);

    const glm::vec3& getAmbient() const { return m_ambient; }
    void setAmbient(const glm::vec3& ambient) { m_ambient = ambient; }
    const glm::vec3& getDiffuse() const { return m_diffuse; }
    void setDiffuse(const glm::vec3& diffuse) { m_diffuse = diffuse; }
    const glm::vec3& getSpecular() const { return m_specular; }
    void setSpecular(const glm::vec3& specular) { m_specular = specular; }


    void prepare(int index, std::shared_ptr<Shader>& shader) const;
};
