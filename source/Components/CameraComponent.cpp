#include "CameraComponent.h"

namespace Cosmo
{
	namespace Components
	{

		void Camera::moveForward(float amount)
		{
			//speedForward += amount;
			speed.z += amount;
			if (speed.z > maxSpeed)
			{
				speed.z = maxSpeed;
			}
			else if (speed.z < -maxSpeed)
			{
				speed.z = -maxSpeed;
			}
		}

		void Camera::moveRight(float amount)
		{
			//speedRight += amount;
			speed.x += amount;
			if (speed.x > maxSpeed)
			{
				speed.x = maxSpeed;
			}
			else if (speed.x < -maxSpeed)
			{
				speed.x = -maxSpeed;
			}
		}

		void Camera::moveUp(float amount)
		{
			speed.y += amount;
			if (speed.y > maxSpeed)
			{
				speed.y = maxSpeed;
			}
			else if (speed.y < -maxSpeed)
			{
				speed.y = -maxSpeed;
			}
		}


	}
}