#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "Event.h"

namespace Cosmo
{
	namespace Events
	{
		class Collision : public Event
		{
		public:
			Collision() : Event(EventType::Collision){}
			Collision(unsigned int id0, unsigned int id1);

			unsigned int id0;
			unsigned int id1;
		};
	}
}

#endif 