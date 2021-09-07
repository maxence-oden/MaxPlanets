#version 120

//textCoord0 = height and biome
varying vec2 textCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;

void main()
{
    gl_FragColor = vec4(1, 0, 0, 1.0);
    //gl_FragColor = texture2D(diffuse, textCoord0) * clamp(dot(-vec3(0,0,1), normal0), 0.0, 1.0); //vec4(1.0, 0.0, 0.0, 1.0);
}