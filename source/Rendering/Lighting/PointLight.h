#pragma once

#include "BaseLight.h"

struct PointLight : public BaseLight
{
    struct Attenuation
    {
        float constant;
        float linear;
        float exp;
    } attenuation;

    glm::vec3 position;


    PointLight()
    {
        attenuation.exp = 0.0f;
        attenuation.linear = 0.0f;
        attenuation.constant = 0.0f;
        position = glm::vec3({ 0.0f,0.0f,0.0f });
    }
};
