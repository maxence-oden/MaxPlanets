#ifndef PLANET_H
#define PLANET_H

#include "transform.h"
#include "mesh.h"
#include "shader.h"
#include "converts.h"

class Planet
{
private:
    Mesh* planetMesh;
    Transform* planetTransform;
    Shader* planetShader;
    float diameter;

    void ProjectVertices(std::vector<glm::vec3>* vertices);
public:
    Planet(Shader* planetShader, const float diameter = 50);
    ~Planet();
    Mesh* GenerateSphere(int density = 3);
    void DrawPlanet(Camera camera) { 
        planetShader->Bind();
        planetShader->Update(*planetTransform, camera);
        planetMesh->Draw(); 
        };
    inline Transform* GetTransform() { return planetTransform; }
};

#endif