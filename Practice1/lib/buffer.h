#pragma once
#include <array>
#include <vector>

struct Vertex;
class Shader;

class Buffer
{
    std::array<uint32_t, 2> m_IDs;
    uint32_t m_NumIndices;
    
public:
    Buffer(std::vector<Vertex> vertices, std::vector<uint16_t> indices);
    void draw(const Shader& shader) const;
};
