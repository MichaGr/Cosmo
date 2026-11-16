#include "UpdateBoundingBoxesSystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/VelocityComponent.h"

#include "../World.h"

#include "../Memory/PoolManager.h"

#include <iostream>
#include <omp.h>

namespace Cosmo
{

	namespace Systems
	{

        void UpdateBoundingBoxesSystem::init(World* world)
		{
            m_world = world;
            m_componentBitset = m_world->initComponentBitset<Components::Position, Components::Velocity, Components::Collider>();
		}

        void UpdateBoundingBoxesSystem::onUpdate()
		{
			startClock();
            EntitySet* entities = m_world->getEntitySet(m_componentBitset);

//            for(auto it = entities->begin(); it != entities->end();++it)
//			{
//                m_world->getComponent<Components::Collider>(*(it)).aabb.pos =
//                    m_world->getComponent<Components::Position>(*(it)) +
//                    m_world->getComponent<Components::Velocity>(*it) * m_deltaTime;
//			}

			stopClock();
		}

		UpdateBoundingBoxesSystem::~UpdateBoundingBoxesSystem()
		{}

	} //namespace Systems

} //namespace Cosmo
