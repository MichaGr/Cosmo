#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "Component.h"
#include "../../glm-0.9.9.3/glm/gtc/matrix_transform.hpp"

namespace Cosmo
{
	namespace Components
	{
		struct Collider : public Component
		{
			Collider() {}
			//AABB
			struct AABB
			{
				glm::vec3 pos;
				glm::vec3 size;
			};

			//OBB
			struct OBB
			{
				glm::vec3 pos;
				glm::vec3 half_size;
				glm::vec3 axisX;
				glm::vec3 axisY;
				glm::vec3 axisZ;
			};

			AABB aabb;
			OBB obb;
		};
	}
}

#endif //COLLIDERCOMPONENT_H