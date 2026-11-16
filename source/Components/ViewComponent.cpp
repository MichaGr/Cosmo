#include "ViewComponent.h"

namespace Cosmo
{
	namespace Components
	{
		void View::resize(float width, float height)
		{
			this->width = width;
			this->height = height;
		}

		float View::aspectRatio() const
		{
			return width / height;
		}
	}
}