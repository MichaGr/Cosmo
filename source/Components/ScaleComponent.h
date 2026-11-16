#ifndef SCALECOMPONENT_H
#define SCALECOMPONENT_H

#include "Component.h"
#include "../../glm-0.9.9.3/glm/vec4.hpp"

namespace Cosmo
{

	namespace Components
	{
		struct Scale : public Component, public glm::vec4
		{
			Scale() { x = 1.0f; y = 1.0f; z = 1.0f; w = 1.0f; }
			Scale(float x, float y, float z, float w = 1.0f)
			{
				this->x = x;
				this->y = y;
				this->z = z;
				this->w = w;
			}

			void set(float x, float y, float z, float w = 1.0f)
			{
				this->x = x;
				this->y = y;
				this->z = z;
				this->w = w;
			}
		};
	} //namespace Components
} //namespace EntityComponentSystem


#endif //SCALECOMPONENT_H
