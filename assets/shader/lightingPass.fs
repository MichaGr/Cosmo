#version 450 core

struct
BaseLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
};

struct
DirectionalLight
{
    BaseLight Base;
    vec3 Direction;
};

struct
Attenuation
{
    float constant;
    float linear;
    float exp;
};

struct
PointLight
{
    BaseLight Base;
    Attenuation Atten;
    vec3 Position;
};

uniform sampler2D gPositionMap;
uniform sampler2D gColorMap;
uniform sampler2D gNormalMap;
uniform sampler1D tex_toon;
uniform DirectionalLight gDirectionalLight;
//uniform PointLight gPointLight;
uniform vec3 gEyeWorldPos;
//uniform float gMatSpecularIntensity;
//uniform float gSpecularPower;
uniform vec3 gScreenSize;

vec4
CalcLightInternal(BaseLight Light, vec3 LightDirection, vec3 Normal)
{
    vec4 AmbientColor = vec4(Light.Color * Light.AmbientIntensity, 1.0);
    float DiffuseFactor = pow(max(0.0,dot(Normal, -LightDirection)),5.0);

    vec4 DiffuseColor  = vec4(0.0, 0.0, 0.0, 0.0);

    if (DiffuseFactor > 0.0) {
        DiffuseColor = vec4(Light.Color * Light.DiffuseIntensity * DiffuseFactor, 1.0);
    }

    return (AmbientColor + DiffuseColor);
}

vec4
CalcDirectionalLight(vec3 Normal)
{
    return CalcLightInternal(gDirectionalLight.Base, gDirectionalLight.Direction, Normal);
}

vec2
CalcTexCoord()
{
    return gl_FragCoord.xy / gScreenSize.xy;
}

out vec4 FragColor;

uniform float b;
uniform float c;
uniform vec3 fogColor;

vec3
applyFog(vec3 rgb, float distance)
{
    float fogAmount = 1.0 - exp(-distance*b);
    return mix(rgb,fogColor,fogAmount);
}

vec3
nonConstantFog(vec3 rgb, float distance, vec3 eyePos, vec3 worldPos)
{
    vec3 rayOri = eyePos;
    vec3 rayDir = worldPos - eyePos;
    float a = c/b;
    float fogAmount = a * exp(-rayOri.y * b) * (1.0 - exp(-distance * rayDir.y*b))/rayDir.y;

    return mix(rgb,fogColor,fogAmount);
}

void
main()
{
        vec2 TexCoord = CalcTexCoord();
        vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
        vec3 Color = texture(gColorMap, TexCoord).xyz;
        vec3 Normal = texture(gNormalMap, TexCoord).xyz;
        Normal = normalize(Normal);
        float distance = distance(WorldPos,gEyeWorldPos);

        float tc = pow(max(0.0, dot(Normal,gDirectionalLight.Direction)),5.0);

//        vec4 color = texture(tex_toon,tc) * (tc * 0.8+0.2);

//        Color = applyFog(Color,distance);
        vec4 col= vec4(Color, 1.0) * CalcDirectionalLight(Normal);
        col = vec4(applyFog(col.rgb,distance),1.0);
//        col = vec4(nonConstantFog(col.rgb,distance,gEyeWorldPos,WorldPos),1.0);
//        col = vec4(Normal,1.0);
        //col = mix(vec4(79.0/255.0, 195.0/255.0, 247.0/255.0,1.0),col,fogFactor);
        FragColor = col;

}
