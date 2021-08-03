#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture0;

out vec3 fragNormal;
out vec3 fragPos;
out vec2 texCoord0;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vec4 position = vec4(aPos, 1.0);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
    
    fragPos = (modelMatrix * position).xyz;
    fragNormal = mat3(transpose(inverse(modelMatrix))) * aNormal;
    
    texCoord0 = aTexture0;
}
