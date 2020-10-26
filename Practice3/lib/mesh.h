#pragma once
#include <memory>
#include <vector>

class Buffer;
class Material;
class Shader;

class Mesh
{
    std::vector<std::pair<std::shared_ptr<Buffer>, Material>* > m_Buffers;

public:
    Mesh() = default;
    void addBuffer(const std::shared_ptr<Buffer>& buffer, const Material& material);
    size_t getNumBuffers() const;
    const std::shared_ptr<Buffer>& getBuffer(size_t index) const;
    std::shared_ptr<Buffer>& getBuffer(size_t index);
    const Material& getMaterial(size_t index) const;
    Material& getMaterial(size_t index);
    void draw();

    static std::shared_ptr<Mesh> load(const char* filename, const std::shared_ptr<Shader>& shader = nullptr);
};
