#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include "transform.h"
#include "camera.h"

class Shader
{
public:
    Shader(const std::string& fileName);

    void Bind();
    void Update(const Transform& transform, const Camera& camera);

    virtual ~Shader();
private:
    static const unsigned int NUM_SHADERS = 2;

    enum
    {
        TRANSFORM_U,
        NUM_UNIFORMS
    };

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    GLuint CreateShader(const std::string& text, GLenum shaderType);

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
};

#endif