#include "EventHandler.h"

namespace Cosmo
{
	void EventHandler::queueEvent(Event* event)
	{
		m_receivedEvents.emplace_back(event);
	}

} //namespace Cosmo