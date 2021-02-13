#ifndef CONVERTS_H
#define CONVERTS_H

#include "mesh.h"

namespace converts
{

Vertex* Convert_vector_to_vertex(std::vector<glm::vec3> vertices);
unsigned int* Convert_vector_to_int(std::vector<glm::vec3> indices);

}
#endif