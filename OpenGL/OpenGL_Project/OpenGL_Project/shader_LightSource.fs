#version 330 core
out vec4 FragColor;

struct LightInfo {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform LightInfo lightInfo;

void main()
{
    FragColor = vec4(lightInfo.specular, 1.0);
}
