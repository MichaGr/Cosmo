#include "MoveForwardSystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/ForwardComponent.h"

#include "../Memory/PoolManager.h"

#include <iostream>
#include <omp.h>
namespace Cosmo
{

	namespace Systems
	{

        void MoveForwardSystem::init(World* world)
		{
//			m_manager = manager;
//			m_componentBitset = m_manager->initComponentBitset<Components::Position, Components::Forward>();
		}

        void MoveForwardSystem::onUpdate()
		{
			startClock();

			std::cout << "SIZE COMPARISON" << std::endl;
//            std::cout << m_manager->getEntityCount() << std::endl;
//			std::cout << m_manager->getEntitySet(m_componentBitset)->size() << std::endl;


//            EntitySet* set = m_manager->getEntitySet(m_componentBitset);
//            for(EntityID id : *set)
//            {
//                Components::Position& p = m_manager->getComponent<Components::Position>(id);
//                Components::Forward& f = m_manager->getComponent<Components::Forward>(id);
//            }
//#pragma omp parallel for
//			for (int i = 0; i < (int)m_manager->getEntityCount(); ++i)
//			{
//				EntityID id = i;
//				if (m_manager->hasComponent<Components::Position>(id) &&
//					m_manager->hasComponent<Components::Forward>(id))
//				{

//				}
//			}

			stopClock();
		}

		MoveForwardSystem::~MoveForwardSystem()
		{}

	} //namespace Systems

} //namespace Cosmo
