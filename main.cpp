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
    Display display(WIDTH, HEIGHT, "Hola chicos!");

    Shader planetShader("./res/planetShader");
    Planet planet(&planetShader);
    Camera camera(glm::vec3(0,0,0), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);

    while (!display.IsClosed())
    {
        display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
        
        planet.GetTransform()->GetRot().y += display.h;
        planet.GetTransform()->GetRot().x += display.v;
        camera.GetPos()->z += display.z;
        planet.DrawPlanet(camera);

        display.Update();
    }
    

    return 0;
}