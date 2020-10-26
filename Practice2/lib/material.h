#pragma once

class Texture;
class Shader;

class Material
{
    std::shared_ptr<Texture> m_Texture;
    std::shared_ptr<Shader> m_Shader;

public:
    Material(const std::shared_ptr<Texture>& tex = nullptr, const std::shared_ptr<Shader>& shader = nullptr);
    const std::shared_ptr<Shader>& getShader() const;
    std::shared_ptr<Shader>& getShader();
    void setShader(const std::shared_ptr<Shader>& shader);
    const std::shared_ptr<Texture>& getTexture() const;
    void setTexture(const std::shared_ptr<Texture>& tex);
    void prepare();
};