#ifndef COLLISIONHANDLERSYSTEM_H
#define COLLISIONHANDLERSYSTEM_H

#include "System.h"
#include "../EventManager/EventHandler.h"
#include "../EventManager/Events/CollisionEvent.h"
#include <iostream>
namespace Cosmo
{
	namespace Systems
	{
		class CollisionHandlerSystem : public System, public EventHandler
		{
		public:
			CollisionHandlerSystem(EventQueue* queue)
				: EventHandler(queue)
			{
				m_name = "CollisionHandlerSystem";
				this->subscribe<Events::Collision>();
			}

			~CollisionHandlerSystem() override
			{}

            void init(World* world) override;
            void onUpdate() override;

		private:
			EntityID colliderID;

		};
	}
}

#endif 
