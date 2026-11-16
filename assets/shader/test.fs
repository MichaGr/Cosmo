#version 450 core

in vec4 Color;
in vec3 normal0;
in vec3 WorldPos0;

struct BaseLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
};

struct DirectionalLight
{
    BaseLight Base;
    vec3 Direction;
};

struct Attenuation
{
    float constant;
    float linear;
    float exp;
};

struct PointLight
{
    BaseLight Base;
    Attenuation Atten;
    vec3 Position;
};


out vec4 color;

uniform DirectionalLight gDirectionalLight;
uniform PointLight gPointLight;

vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, vec3 Normal)
{
    vec4 AmbientColor = vec4(Light.Color * Light.AmbientIntensity, 1.0);
    float DiffuseFactor = dot(Normal, -LightDirection);

    vec4 DiffuseColor  = vec4(0.0, 0.0, 0.0, 0.0);

    if (DiffuseFactor > 0.0) {
        DiffuseColor = vec4(Light.Color * Light.DiffuseIntensity * DiffuseFactor, 1.0);
    }

    return (AmbientColor + DiffuseColor);
}

vec4 CalcDirectionalLight(vec3 Normal)
{
    return CalcLightInternal(gDirectionalLight.Base, gDirectionalLight.Direction, Normal);
}

vec4 CalcPointLight(vec3 Normal)
{
    vec3 LightDirection = WorldPos0 - gPointLight.Position;
    float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);
    vec4 Color = CalcLightInternal(gPointLight.Base, LightDirection, Normal);
    float Attenuation =  gPointLight.Atten.constant +
                         gPointLight.Atten.linear * Distance +
                         gPointLight.Atten.exp * Distance * Distance;


    return Color / Attenuation;
}


void main()
{
    vec3 Normal = normalize(normal0);
    vec4 TotalLight = CalcDirectionalLight(Normal);

    TotalLight += 0.1 * CalcPointLight(Normal);
    color = vec4(1.0) * TotalLight;
}
