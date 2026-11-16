#ifndef ONGROUNDCOMPONENT_H
#define ONGROUNDCOMPONENT_H

#include "Component.h"

namespace Cosmo
{
	namespace Components
	{
		struct OnGround : public Component
		{
			bool set;

			void operator=(const bool& rhs)
			{
				set = rhs;
			}

			operator bool()
			{
				return set;
			}
		};
	}
}

#endif