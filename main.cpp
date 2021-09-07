#include <iostream>
#include <GL/glew.h>
#include "src/display.h"
#include "src/shader.h"
#include "src/mesh.h"
#include "src/texture.h"
#include "src/transform.h"
#include "src/camera.h"
#include "src/planet.h"

#define WIDTH 1800
#define HEIGHT 1000

int main()
{
    size_t counter = 0;
    Display display(WIDTH, HEIGHT, "Hola chicos!");

    Shader planetShader("./res/planetShader");
    Planet planet(&planetShader);
    Camera camera(glm::vec3(0,0,0), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
    

    size_t len = planet.GetMesh()->GetModel()->texCoords.size();

    while (!display.IsClosed())
    {
        display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
        
        planet.GetTransform()->GetRot().y += display.h;
        planet.GetTransform()->GetRot().x += display.v;
        planet.GetMesh()->GetModel()->texCoords[counter].x = 0;
        planet.GetMesh()->GetModel()->texCoords[counter].y = 0;
        *camera.GetPos() += display.z * *camera.GetForward();
        planet.DrawPlanet(camera);

        display.Update();
        counter += 1;
        if (counter >= len-1)
            counter = 0;
    }
    

    return 0;
}