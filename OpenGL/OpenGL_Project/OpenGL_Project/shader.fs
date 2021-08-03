#version 330 core
struct SurfaceProperties {
    sampler2D diffuseTex;
    sampler2D specularTex;
    float shininess;
};

in vec3 fragNormal;
in vec3 fragPos;
in vec2 texCoord0;

out vec4 FragColor;

uniform SurfaceProperties surfaceProperties;
uniform vec3 viewPos;

// Point Lights
struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    vec3 position;
    vec3 polynom;
};
#define MAX_POINT_LIGHTS 8
uniform int pointLightsCnt;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

// Spot Lights
struct SpotLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    vec3 position;
    vec3 direction;
    vec3 polynom;
    float cutOff;
    float outerCutOff;
};
#define MAX_SPOT_LIGHTS 8
uniform int spotLightsCnt;
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

// Directional Lights
struct DirectionalLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    vec3 direction;
};
#define MAX_DIRECTIONAL_LIGHTS 2
uniform int directionalLightsCnt;
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];

// Ambient Lights
struct AmbientLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define MAX_AMBIENT_LIGHTS 1
uniform int ambientLightsCnt;
uniform AmbientLight ambientLights[MAX_AMBIENT_LIGHTS];

vec3 processDirectionalLights(vec4 diffuseSample, vec4 specularSample, vec3 normal) {
    vec3 result = vec3(0.0);
    vec3 viewDir = normalize(viewPos - fragPos);
    for (int i = 0; i < directionalLightsCnt; ++i) {
        vec3 lightDir = normalize(-directionalLights[i].direction);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), surfaceProperties.shininess);
        
        // ambient
        result += directionalLights[i].ambient  * diffuseSample.rgb;
        // diffuse
        result += directionalLights[i].diffuse  * diff * diffuseSample.rgb;
        // specular
        result += directionalLights[i].specular * spec * specularSample.rgb;
    }
    return result;
}

vec3 processPointLights(vec4 diffuseSample, vec4 specularSample, vec3 normal) {
    vec3 result = vec3(0.0);
    vec3 viewDir = normalize(viewPos - fragPos);
    for (int i = 0; i < pointLightsCnt; ++i) {
        vec3 lightDir = normalize(pointLights[i].position - fragPos);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), surfaceProperties.shininess);
        // attenuation
        float d    = length(pointLights[i].position - fragPos);
        float attenuation = 1.0 / (pointLights[i].polynom.x + pointLights[i].polynom.y * d +
                                   pointLights[i].polynom.z * (d * d));
        // combine results
        vec3 ambient  = pointLights[i].ambient  * diffuseSample.rgb;
        vec3 diffuse  = pointLights[i].diffuse  * diff * diffuseSample.rgb;
        vec3 specular = pointLights[i].specular * spec * specularSample.rgb;
        ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;
        result += ambient;
        result += diffuse;
        result += specular;
    }
    return result;
}

vec3 processSpotLights(vec4 diffuseSample, vec4 specularSample, vec3 normal) {
    vec3 result = vec3(0.0);
    vec3 viewDir = normalize(viewPos - fragPos);
    for (int i = 0; i < spotLightsCnt; ++i) {
        vec3 lightDir = normalize(spotLights[i].position - fragPos);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), surfaceProperties.shininess);
        // attenuation
        float d = length(spotLights[i].position - fragPos);
        float attenuation = 1.0 / (spotLights[i].polynom.x + spotLights[i].polynom.y * d + spotLights[i].polynom.z * (d * d));
        // spotlight intensity
        float theta = dot(lightDir, normalize(-spotLights[i].direction));
        float epsilon = spotLights[i].cutOff - spotLights[i].outerCutOff;
        float intensity = clamp((theta - spotLights[i].outerCutOff) / epsilon, 0.0, 1.0);
        // combine results
        vec3 ambient = spotLights[i].ambient * diffuseSample.rgb;
        vec3 diffuse = spotLights[i].diffuse * diff * diffuseSample.rgb;
        vec3 specular = spotLights[i].specular * spec * specularSample.rgb;
        ambient *= attenuation * intensity;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;
        result += ambient;
        result += diffuse;
        result += specular;
    }
    return result;
}

vec3 processAmbientLights(vec4 diffuseSample) {
    vec3 result = vec3(0.0);
    for (int i = 0; i < ambientLightsCnt; ++i) {
        result += ambientLights[i].ambient * diffuseSample.rgb;
    }
    return result;
}

void main()
{
    vec4 result = vec4(0.0);
    
    // Process Lighting
    vec4 diffuseSample = texture(surfaceProperties.diffuseTex, texCoord0);
    vec4 specularSample = texture(surfaceProperties.specularTex, texCoord0);
    
    vec3 normal = normalize(fragNormal);
    result.rgb += processDirectionalLights(diffuseSample, specularSample, normal);
    result.rgb += processPointLights(diffuseSample, specularSample, normal);
    result.rgb += processSpotLights(diffuseSample, specularSample, normal);
    result.rgb += processAmbientLights(diffuseSample);

    FragColor = result;
}
