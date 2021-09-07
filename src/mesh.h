#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include "obj_loader.h"

class Vertex
{
public:
    Vertex(const glm::vec3& pos = glm::vec3(0,0,0), const glm::vec2 textCoord = glm::vec2(0,0), const glm::vec3& normal = glm::vec3(0,0,0))
    {
        this->pos = pos;
        this->textCoord = textCoord;
        this->normal = normal;
    }

    inline glm::vec3* GetPos() { return &pos; }
    inline glm::vec2* GetTextCoord() { return &textCoord; }
    inline glm::vec3* GetNormal() { return &normal; }
private:
    glm::vec3 pos;
    glm::vec2 textCoord;
    glm::vec3 normal;
};



class Mesh
{
public:
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
    Mesh(const std::string& fileName);

    void Draw();

    inline IndexedModel* GetModel() { return &model; };

    virtual ~Mesh();
private:
    enum
    {
        POSITION_VB,
        TEXTCOORD_VB,
        NORMAL_VB,

        INDEX_VB,

        NUM_BUFFERS
    };

    void InitMesh();

    IndexedModel model;
    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif