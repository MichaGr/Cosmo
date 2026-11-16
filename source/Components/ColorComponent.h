#ifndef Cosmo_COLORCOMPONENT_H
#define Cosmo_COLORCOMPONENT_H

#include "Component.h"
#include "../glm-0.9.9.3/glm/vec4.hpp"
namespace Cosmo
{

namespace Components
{

	struct Color : public Component, public glm::vec4
	{
		Color() { r = 0.0f; g = 0.0f; b = 0.0f; a = 1.0f; }
		Color(float r, float g, float b, float a = 1.0f)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		void set(float r, float g, float b, float a = 1.0f)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
	};

} //namespace Components

} //namespace Cosmo

#endif //Cosmo_COLORCOMPONENT_H
