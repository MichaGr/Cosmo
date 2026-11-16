#ifndef EVENT_H
#define EVENT_H

namespace Cosmo
{
		enum EventType
		{
			Collision = 0,
			Count
		};

		class Event
		{
		public:
			Event(EventType type) : m_type(type) {}
			EventType getType() { return m_type; }
		protected:
			EventType m_type;
		};
	
}

#endif