#version 120

attribute vec3 position;
attribute vec2 textCoord;
attribute vec3 normal;

varying vec2 textCoord0;
varying vec3 normal0;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0);
    textCoord0 = textCoord;
    normal0 = (transform * vec4(normal, 0.0)).xyz; //Just rotate and scaling
}