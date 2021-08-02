#version 330 core
struct SurfaceProperties {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 fragNormal;
in vec3 fragPos;

out vec4 FragColor;

uniform SurfaceProperties surfaceProperties;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // ambient
    vec3 ambient = lightColor * surfaceProperties.ambient;
    
    // diffuse
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * diff * surfaceProperties.diffuse;
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), surfaceProperties.shininess);
    
    vec3 specular = spec * lightColor * surfaceProperties.diffuse;
    
    vec4 result = vec4(ambient + diffuse + specular, 1.0);
    FragColor = result;
}
