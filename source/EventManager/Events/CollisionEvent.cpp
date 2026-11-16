#include "CollisionEvent.h"

namespace Cosmo
{
	namespace Events
	{
		Collision::Collision(unsigned int id0, unsigned int id1)
			: Event(EventType::Collision),
			id0(id0),
			id1(id1)
		{}
	}
}