#include "converts.h"

Vertex* converts::Convert_vector_to_vertex(std::vector<glm::vec3> vertices)
{
    size_t len = vertices.size();

    Vertex* newvertices = new Vertex[len];

    for (size_t i = 0; i < len; i++)
    {
        newvertices[i].GetPos()->x = vertices.at(i).x;
        newvertices[i].GetPos()->y = vertices.at(i).y;
        newvertices[i].GetPos()->z = vertices.at(i).z;
        newvertices[i].GetTextCoord()->x = vertices.at(i).x;
        newvertices[i].GetTextCoord()->y = vertices.at(i).y;
    }
    
    return newvertices;
}

unsigned int* converts::Convert_vector_to_int(std::vector<glm::vec3> indices)
{
    size_t len = indices.size()*3;

    unsigned int* newindices = new unsigned int[len];

    for (size_t i = 0; i < len; i+=3)
    {
        newindices[i] = indices.at(i/3).x;
        newindices[i+1] = indices.at(i/3).y;
        newindices[i+2] = indices.at(i/3).z;
    }
    
    return newindices;
}