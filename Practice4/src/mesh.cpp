#include "../lib/mesh.h"
#include "../lib/buffer.h"
#include "../lib/material.h"
#include "../lib/state.h"
#include "../lib/shader.h"
#include "../lib/vertex.h"
#include "../lib/texture.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../lib/tinyobjloader-master/tiny_obj_loader.h"

void Mesh::addBuffer(const std::shared_ptr<Buffer>& buffer, const Material& material)
{
    m_Buffers.push_back(new std::pair<std::shared_ptr<Buffer>, Material>(buffer, material));
}

size_t Mesh::getNumBuffers() const
{
    return m_Buffers.size();
}

const std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index) const
{
    return m_Buffers.at(index)->first;
}

std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index)
{
    return m_Buffers.at(index)->first;
}

const Material& Mesh::getMaterial(size_t index) const
{
    return m_Buffers.at(index)->second;
}

Material& Mesh::getMaterial(size_t index)
{
    return m_Buffers.at(index)->second;
}

void Mesh::draw()
{
    for (unsigned int idx = 0; idx < m_Buffers.size(); ++idx)
    {
        m_Buffers[idx]->second.prepare();
        m_Buffers[idx]->first->draw(*State::defaultShader);
    }
}

std::shared_ptr<Mesh> Mesh::load(const char* filename, const std::shared_ptr<Shader>& shader)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename))
    {
        throw std::runtime_error(warn + err);
    }

    std::shared_ptr<Mesh> MeshAux = std::make_shared<Mesh>();
    std::shared_ptr<Material> MaterialAux = std::make_shared<Material>(nullptr, shader);

    for (const auto& shape : shapes)
    {
        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;
        for (const auto& index : shape.mesh.indices)
        {
            Vertex* vertexAux = new Vertex();

            // Position
            vertexAux->m_Position.x = attrib.vertices[3 * index.vertex_index + 0];
            vertexAux->m_Position.y = attrib.vertices[3 * index.vertex_index + 1];
            vertexAux->m_Position.z = attrib.vertices[3 * index.vertex_index + 2];

            // Color
            vertexAux->m_Color.x = 1;
            vertexAux->m_Color.y = 1;
            vertexAux->m_Color.z = 1;

            // Texture
            vertexAux->m_TextureCoord.x = attrib.texcoords[2 * index.texcoord_index + 0];
            vertexAux->m_TextureCoord.y = attrib.texcoords[2 * index.texcoord_index + 1];

            // Normal
            vertexAux->m_Normal.x = attrib.normals[3 * index.normal_index + 0];
            vertexAux->m_Normal.y = attrib.normals[3 * index.normal_index + 1];
            vertexAux->m_Normal.z = attrib.normals[3 * index.normal_index + 2];

            // Add vertex and vertex index to the array
            vertices.push_back(*vertexAux);
            indices.push_back(static_cast<uint16_t>(indices.size()));
        }
        MeshAux->addBuffer(std::make_shared<Buffer>(vertices, indices), *MaterialAux);
    }

    int i = 0;
    for (const auto& material : materials)
    {
        if (material.ambient_texname != "")
        {
            std::string textPath = "data/" + material.ambient_texname;
            MeshAux->getMaterial(i).setTexture(Texture::load(textPath.data()));
            MeshAux->getMaterial(i).setShader(State::defaultShader);

            MeshAux->getMaterial(i).setAmbient(glm::vec3(material.ambient[0], material.ambient[1], material.ambient[2]));
            MeshAux->getMaterial(i).setDiffuse(glm::vec3(material.diffuse[0], material.diffuse[1], material.diffuse[2]));
            MeshAux->getMaterial(i).setSpecular(glm::vec3(material.specular[0], material.specular[1], material.specular[2]));
            MeshAux->getMaterial(i).setShininess(static_cast<uint8_t>(material.shininess));
        }
        i++;
    }

    return MeshAux;
}
