#include "EventQueue.h"
#include "EventHandler.h"

namespace Cosmo
{
	void EventQueue::broadCast()
	{
		for (Event* e : m_queuedEvents)
		{
			for (EventHandler* handler : m_subscriber.at(e->getType()))
			{
				handler->queueEvent(e);
			}
		}
		m_queuedEvents.clear();
	}

	void EventQueue::queueEvent(Event* event)
	{
		m_queuedEvents.emplace_back(event);
	}
}