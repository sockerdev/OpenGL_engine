#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vec4 position = vec4(aPos, 1.0);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
}
