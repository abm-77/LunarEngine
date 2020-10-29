#version 330 core

#define MAX_DIFFUSE_TEXTURES 3
#define MAX_SPECULAR_TEXTURES 3

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;



struct Material
{
    vec3 emissive;
    sampler2D diffuse[MAX_DIFFUSE_TEXTURES];
    sampler2D specular[MAX_SPECULAR_TEXTURES];
    float shininess;
};

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    
    float cutoff;
    float outerCutoff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform DirectionalLight dirLight;
uniform SpotLight spotLight;
#define N_POINT_LIGHTS 4
uniform PointLight pointLights[N_POINT_LIGHTS];
uniform vec3 viewPos;
uniform vec3 lightColor;


out vec4 FragColor;

vec3 CalculateAmbient(vec3 lightAmbient)
{
    vec3 ambient = vec3(0.0);

    for (int i = 0; i < MAX_DIFFUSE_TEXTURES; i++)
    {
        ambient += lightAmbient * vec3(texture(material.diffuse[i], TexCoords));
	}

    return ambient;
}

vec3 CalculateDiffuse (float diff, vec3 lightDiffuse)
{
    vec3 diffuse = vec3(0.0);
    
    for (int i = 0; i < MAX_DIFFUSE_TEXTURES; i++)
    {
        diffuse += lightDiffuse * diff * vec3(texture(material.diffuse[i], TexCoords));
	}

    return diffuse;
}

vec3 CalculateSpecular (float spec, vec3 lightSpecular)
{
    vec3 specular = vec3(0.0);
    
    for (int i = 0; i < MAX_DIFFUSE_TEXTURES; i++)
    {
        specular += lightSpecular * spec * vec3(texture(material.specular[i], TexCoords));
	}

    return specular;
}

vec3 CalculateDirectionalLight (DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir                   = normalize(-light.direction);
   
   // diffuse shading
    float diff                      = max(dot(normal, lightDir), 0.0);
    
    // specular shading
    vec3 reflectDir                 = reflect(-lightDir, normal);
    float spec                      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   
   // combine results
    vec3 ambient                    = CalculateAmbient(light.ambient);
    vec3 diffuse                    = CalculateDiffuse(diff, light.diffuse);
    vec3 specular                   = CalculateSpecular(spec, light.specular);
   
   return (ambient + diffuse + specular);
}

vec3 CalculatePointLight (PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir               = normalize (light.position - fragPos);
 
    // diffuse 
    float diff                  = max(dot(normal, lightDir), 0.0);

    // specular
    vec3 reflectDir             = reflect(-lightDir, normal);  
    float spec                  = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance = length (light.position - fragPos);
    float attenuation = 1.0 / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));

    // combine results
    vec3 ambient                    = CalculateAmbient(light.ambient);
    vec3 diffuse                    = CalculateDiffuse(diff, light.diffuse);
    vec3 specular                   = CalculateSpecular(spec, light.specular);

    ambient     *= attenuation;
    diffuse     *= attenuation;
    specular    *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight (SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
    
    // combine results
    vec3 ambient                    = CalculateAmbient(light.ambient);
    vec3 diffuse                    = CalculateDiffuse(diff, light.diffuse);
    vec3 specular                   = CalculateSpecular(spec, light.specular);
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}


void main ()
{

    vec3 output         = vec3(0.0);

    vec3 norm           = normalize(Normal);
    vec3 viewDir        = normalize (viewPos - FragPos);

    // Directional Light:
    output += CalculateDirectionalLight (dirLight, norm, viewDir);

    // Point Lighting:
    for (int i = 0; i < N_POINT_LIGHTS; i++)
        output += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);

    // Calculate Spotlight:
    output += CalculateSpotLight(spotLight, norm, FragPos, viewDir);


    FragColor                   = vec4(output, 1.0);
}