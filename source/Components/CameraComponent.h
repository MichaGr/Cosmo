#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"
#include "../glm-0.9.9.3/glm/gtc/matrix_transform.hpp"

namespace Cosmo
{
	namespace Components
	{
		struct Camera : public Component
		{
			void moveForward(float amount);
			void moveRight(float amount);
			void moveUp(float amount);

			glm::vec3 position;
			glm::vec3 speed;
			float horizontalAngle;
			float verticalAngle;
			float maxSpeed;

			glm::mat4 view;

			glm::vec3 direction;
			glm::vec3 right;
			glm::vec3 up;

			float zoom;

		};
	}
}

#endif //CAMERACOMPONENT_H
