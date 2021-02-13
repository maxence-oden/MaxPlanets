#include "planet.h"

Planet::Planet(Shader* planetShader, const float diameter)
{
    this->planetShader = planetShader;
    this->diameter = diameter;
    planetMesh = GenerateSphere(8);
    planetTransform = new Transform();
}

Planet::~Planet()
{
    delete planetTransform;
    delete planetMesh;
}

glm::vec3 Bisection(glm::vec3 vec1, glm::vec3 vec2)
{
    glm::vec3 newvertice;
    
    newvertice = vec1 - vec2;
    newvertice /= 2;
    newvertice += vec2;

    return newvertice;
}

void SubdivideTriangle(std::vector<glm::vec3>* vertices, std::vector<glm::vec3>* indices, glm::vec3 Indice)
{
    glm::vec3 vertice1 = vertices->at(Indice.x);
    glm::vec3 vertice2 = vertices->at(Indice.y);
    glm::vec3 vertice3 = vertices->at(Indice.z);

    glm::vec3 newvertice(0,0,0);

    vertices->push_back(Bisection(vertice3, vertice2));
    vertices->push_back(Bisection(vertice3, vertice1));
    vertices->push_back(Bisection(vertice1, vertice2));

    size_t size = vertices->size();
    indices->push_back(glm::vec3(Indice.x, size-2, size-1));
    indices->push_back(glm::vec3(size-1, size-3, Indice.y));
    indices->push_back(glm::vec3(size-2, Indice.z, size-3));
    indices->push_back(glm::vec3(size-2, size-3, size-1));
}

std::vector<glm::vec3> SubdivideIco(std::vector<glm::vec3>* vertices, std::vector<glm::vec3> indices)
{
    std::vector<glm::vec3> newIndices;
    for (size_t i = 0; i < indices.size(); i++)
    {
        SubdivideTriangle(vertices, &newIndices, indices.at(i));
    }
    return newIndices;
}

void Planet::ProjectVertices(std::vector<glm::vec3>* vertices)
{
    for (size_t i = 0; i < vertices->size(); i++)
    {
        glm::vec3* vertice = &vertices->at(i);
        float lenvertice = sqrt(powf32(vertice->x, 2) + powf32(vertice->y, 2) + powf32(vertice->z, 2));
        float q = (this->diameter + (3 * (rand()%100)/100)) / lenvertice;
        vertice->x *= q;
        vertice->y *= q;
        vertice->z *= q;
    }
    
}

Mesh* Planet::GenerateSphere(int density)
{
    //GENERATE ICOSAHEDRON
    const float X = 0.525731112119133606f;
    const float Z = 0.850650808362033932f;
    const float N = 0.0f;

    std::vector<glm::vec3> vertices;
    vertices.push_back(glm::vec3(-X,N,Z));
    vertices.push_back(glm::vec3(X,N,Z));
    vertices.push_back(glm::vec3(-X,N,-Z));
    vertices.push_back(glm::vec3(X,N,-Z));
    vertices.push_back(glm::vec3(N,Z,X));
    vertices.push_back(glm::vec3(N,Z,-X));
    vertices.push_back(glm::vec3(N,-Z,X));
    vertices.push_back(glm::vec3(N,-Z,-X));
    vertices.push_back(glm::vec3(Z,X,N));
    vertices.push_back(glm::vec3(-Z,X,N));
    vertices.push_back(glm::vec3(Z,-X,N));
    vertices.push_back(glm::vec3(-Z,-X,N));

    std::vector<glm::vec3> indices;

    indices.push_back(glm::vec3(0,4,1));
    indices.push_back(glm::vec3(0,9,4));
    indices.push_back(glm::vec3(9,5,4));
    indices.push_back(glm::vec3(4,5,8));
    indices.push_back(glm::vec3(4,8,1));
    
    indices.push_back(glm::vec3(8,10,1));
    indices.push_back(glm::vec3(8,3,10));
    indices.push_back(glm::vec3(5,3,8));
    indices.push_back(glm::vec3(5,2,3));
    indices.push_back(glm::vec3(2,7,3));

    indices.push_back(glm::vec3(7,10,3));
    indices.push_back(glm::vec3(7,6,10));
    indices.push_back(glm::vec3(7,11,6));
    indices.push_back(glm::vec3(11,0,6));
    indices.push_back(glm::vec3(0,1,6));

    indices.push_back(glm::vec3(6,1,10));
    indices.push_back(glm::vec3(9,0,11));
    indices.push_back(glm::vec3(9,11,2));
    indices.push_back(glm::vec3(9,2,5));
    indices.push_back(glm::vec3(7,2,11));

    //Subdivide
    for (int i = 1; i < density; i++)
    {
        indices = SubdivideIco(&vertices, indices);
    }

    //Projection
    ProjectVertices(&vertices);

    return new Mesh(converts::Convert_vector_to_vertex(vertices), vertices.size(), converts::Convert_vector_to_int(indices), indices.size()*3);
}