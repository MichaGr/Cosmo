#pragma once

#include "BaseLight.h"

struct DirectionalLight : public BaseLight
{
	glm::vec3 direction;

	DirectionalLight()
	{
		direction = glm::vec3({ 0.0f,0.0f,0.0f });
	}
};