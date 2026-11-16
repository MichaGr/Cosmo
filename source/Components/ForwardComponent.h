#ifndef Cosmo_FORWARDCOMPONENT_H
#define Cosmo_FORWARDCOMPONENT_H

#include "Component.h"
#include "../../glm-0.9.9.3/glm/vec4.hpp"

namespace Cosmo
{

	namespace Components
	{
		struct Forward : public Component, public glm::vec4
		{
			Forward() { x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f; }
			Forward(float x, float y, float z, float w = 1.0f)
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

} //namespace Cosmo

#endif //Cosmo_FORWARDCOMPONENT_H
