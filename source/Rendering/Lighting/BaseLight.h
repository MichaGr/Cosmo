#pragma once

#include <string>
#include "../../../glm-0.9.9.3/glm/vec3.hpp"

struct BaseLight
{
	std::string name;
	glm::vec3 color;
	float ambientIntensity;
	float diffuseIntensity;

	BaseLight()
	{
		color = glm::vec3({ 0.0f,0.0f,0.0f });
		ambientIntensity = 0.0f;
		diffuseIntensity = 0.0f;
	}
};