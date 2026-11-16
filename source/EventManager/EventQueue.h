#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <vector>
#include <unordered_map>

#include "Events/Event.h"
#include <iostream>

namespace Cosmo
{

	class EventHandler;

	class EventQueue
	{
	public:

		void queueEvent(Event* event);

		template <typename T>
		void subscribe(EventHandler* handler)
		{
			Event* e = static_cast<Event*>(new T());
			if (m_subscriber.find(e->getType()) == m_subscriber.end())
			{
				std::vector<EventHandler*> tmpVec;
				m_subscriber.insert(std::make_pair(e->getType(), tmpVec));
			}
			m_subscriber[e->getType()].emplace_back(handler);

			std::cout << "Type: " << e->getType() << " "<< m_subscriber.at(e->getType()).size() << std::endl;
		}

		void broadCast();

	private:

		std::vector<Event*> m_queuedEvents;
		std::unordered_map<EventType, std::vector<EventHandler*> > m_subscriber;

	};

} //namespace Cosmo

#endif //EVENTQUEUE_H