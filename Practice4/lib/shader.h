#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

enum class EShaderType
{
    ST_Vertex,
    ST_Fragment
};

class Shader
{
    GLuint m_ID;
    char* m_Error;

    GLint m_vposLoc;
    GLint m_vcolorLoc;
    GLint m_vtextLoc;
    GLint m_vnormalLoc;

    uint32_t createShader(const char* shaderSource, EShaderType type);
    void createProgram(uint32_t vertex, uint32_t fragment);

public:
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
    ~Shader();

    // Devuelve el identificador de OpenGL del programa
    uint32_t getId() const;

    // Obtiene el mensaje de error generado al compilar o enlazar
    const char* getError() const;

    // Activa el uso de este programa
    void use() const;

    // Activa la escritura de las variables attribute y especifica su formato
    void setupAttribs() const;

    // Obtiene la localización de una variable uniform
    int getLocation(const char* name) const;

    // Da valor a una variable uniform
    void setInt(int loc, int val);
    void setFloat(int loc, float val);
    void setVec3(int loc, const glm::vec3& vec);
    void setVec4(int loc, const glm::vec4& vec);
    void setMatrix(int loc, const glm::mat4& matrix);
};
