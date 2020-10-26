#pragma once
#include "glm/detail/type_vec3.hpp"
#include "glm/detail/type_vec4.hpp"

class Texture;
class Shader;

class Material
{
    std::shared_ptr<Texture> m_Texture;
    std::shared_ptr<Shader> m_Shader;
    glm::vec4 m_Color;
    uint8_t m_Shininess;

    // Light material properties
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

public:
    Material(const std::shared_ptr<Texture>& tex = nullptr, const std::shared_ptr<Shader>& shader = nullptr);
    const std::shared_ptr<Shader>& getShader() const;
    std::shared_ptr<Shader>& getShader();
    void setShader(const std::shared_ptr<Shader>& shader);
    const std::shared_ptr<Texture>& getTexture() const;
    void setTexture(const std::shared_ptr<Texture>& tex);
    const glm::vec4& getColor() const;
    void setColor(const glm::vec4& color);
    uint8_t getShininess() const;
    void setShininess(uint8_t shininess);
    glm::vec3 getAmbient() const;
    void setAmbient(const glm::vec3& ambient);
    glm::vec3 getDiffuse() const;
    void setDiffuse(const glm::vec3& diffuse);
    glm::vec3 getSpecular() const;
    void setSpecular(const glm::vec3& specular);
    void prepare();
};