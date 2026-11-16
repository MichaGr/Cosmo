#ifndef Cosmo_ROTATIONCOMPONENT_H
#define Cosmo_ROTATIONCOMPONENT_H

#include "Component.h"
#include "../../glm-0.9.9.3/glm/gtc/quaternion.hpp"
namespace Cosmo
{

namespace Components
{

struct Rotation : public Component, public glm::quat
{
	Rotation() { x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f; }

	void fromEulerAngles(float x, float y, float z)
	{
		glm::quat q = glm::quat(glm::vec3({ x,y,z }));
		this->x = q.x;
		this->y = q.y;
		this->z = q.z;
		this->w = 1;
	}
};

} //namespace Components

} //namespace Cosmo

#endif //Cosmo_ROTATIONCOMPONENT_H
