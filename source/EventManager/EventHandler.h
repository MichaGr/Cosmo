#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "EventQueue.h"


namespace Cosmo
{
	class EventHandler
	{
	public:
		EventHandler(EventQueue* queue)
			: m_queue(queue)
		{}

		template <typename T>
		void subscribe()
		{
			m_queue->subscribe<T>(this);
		}

		void queueEvent(Event* event);

	protected:
		EventQueue* m_queue;
		std::vector<Event*> m_receivedEvents;
	};
}

#endif 