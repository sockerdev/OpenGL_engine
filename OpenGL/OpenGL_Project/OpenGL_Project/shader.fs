#version 330 core
struct SurfaceProperties {
    sampler2D diffuseTex;
    sampler2D specularTex;
    float shininess;
};

struct LightInfo {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fragNormal;
in vec3 fragPos;
in vec2 texCoord0;

out vec4 FragColor;

uniform SurfaceProperties surfaceProperties;
uniform LightInfo lightInfo;
uniform vec3 viewPos;

void main()
{
    vec4 diffuseSample = texture(surfaceProperties.diffuseTex, texCoord0);
    vec4 specularSample = texture(surfaceProperties.specularTex, texCoord0);
    
    // ambient
    vec3 ambient = lightInfo.ambient * diffuseSample.rgb;
    
    // diffuse
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightInfo.position - fragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightInfo.diffuse * diff * diffuseSample.rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), surfaceProperties.shininess);
    
    vec3 specular = spec * lightInfo.specular * specularSample.rgb;
    
    vec4 result = vec4(ambient + diffuse + specular, 1.0);
    FragColor = result;
}
