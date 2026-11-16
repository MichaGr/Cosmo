#ifndef VIEWCOMPONENT_H
#define VIEWCOMPONENT_H

#include "Component.h"
#include "../glm-0.9.9.3/glm/gtc/matrix_transform.hpp"

namespace Cosmo
{

	namespace Components
	{
		struct View : public Component
		{

			void resize(float width, float height);
			float aspectRatio() const;
			float width;
			float height;
			float fov;

			float nearPlane;
			float farPlane;

			glm::mat4 projection;
		};
	}

} //namespace Cosmo

#endif //VIEWCOMPONENT_H