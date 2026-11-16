#include "CollisionHandlerSystem.h"
#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/OnGroundComponent.h"
#include "../Components/ScaleComponent.h"
#include "../Memory/PoolManager.h"

#include <iostream>
namespace Cosmo
{
	namespace Systems
	{
        void CollisionHandlerSystem::init(World* world)
		{
            m_world = world;
			colliderID = 0;
		}

        void CollisionHandlerSystem::onUpdate()
		{
			startClock();

//			//handle received Events
//			if (m_receivedEvents.size() > 0)
//			{
//				for (Event* e : m_receivedEvents)
//				{
//					Events::Collision* col = static_cast<Events::Collision*>(e);

//					EntityID id0 = col->id0;
//					EntityID id1 = col->id1;

//					Components::Position& p0 = m_manager->getComponent<Components::Position>(id0);
//					Components::Position& p1 = m_manager->getComponent<Components::Position>(id1);

//					Components::Scale& s0 = m_manager->getComponent<Components::Scale>(id0);
//					Components::Scale& s1 = m_manager->getComponent<Components::Scale>(id1);
//					Components::Velocity& v = m_manager->getComponent<Components::Velocity>(id0);

//					//float dX = p0.pos.x - p1.pos.x;
//					//float absDX = abs(dX);
//					//float dY = p0.pos.y - p1.pos.y;
//					//float absDY = abs(dY);
//					//float dZ = p0.pos.z - p1.pos.z;
//					//float absDZ = abs(dZ);

//					//float vx = v.velocity.x;
//					//float vy = v.velocity.y;
//					//float vz = v.velocity.z;

//					bool& f = m_manager->getComponent<Components::OnGround>(id0).set;



//					if (!f && v.y < 0.0f &&
//						abs(p0.x - p1.x) <= abs(p0.y - p1.y) &&
//						abs(p0.z - p1.z) <= abs(p0.y - p1.y))
//					{
//						m_manager->getComponent<Components::OnGround>(id0) = true;
//						m_manager->getComponent<Components::Velocity>(id0).y = 0.0f;
//						m_manager->getComponent<Components::Position>(id0).y = s1.y +
//							p1.y;
//						colliderID = id1;
//					}

//					//if (absDX >= absDY &&
//					//	//absDX >= absDZ &&
//					//	vx > 0.0 &&
//					//	absDY < 1.0)
//					//{
//					//	m_manager->getComponent<Components::Velocity>(id0)->velocity.x = 0.0f;
//					//	if (p0.pos.x > p1.pos.x)
//					//	{
//					//		m_manager->getComponent<Components::Position>(id0)->pos.x = p1.pos.x + 1.0f;
//					//	}
//					//	if (p0.pos.x < p1.pos.x)
//					//	{
//					//		m_manager->getComponent<Components::Position>(id0)->pos.x = p1.pos.x - 1.0f;
//					//	}
//					//	//v.velocity.x = 0.0f;

//					//	//p0.pos.x = p0.pos.x + dX;
//					//}

//					//if (absDZ >= absDX &&
//					//	//absDZ >= absDY &&
//					//	vz > 0.0 &&
//					//	absDY < 1.0)
//					//{
//					//	m_manager->getComponent<Components::Velocity>(id0)->velocity.z = 0.0;
//					//	//v.velocity.z = 0.0f;
//					//	//p0.pos.z = p0.pos.z + dZ;
//					//	m_manager->getComponent<Components::Position>(id0)->pos.z = p0.pos.z + dZ;

//					//	if (p0.pos.z > p1.pos.z)
//					//	{
//					//		m_manager->getComponent<Components::Position>(id0)->pos.z = p1.pos.z + 1.0f;
//					//	}
//					//	if (p0.pos.z < p1.pos.z)
//					//	{
//					//		m_manager->getComponent<Components::Position>(id0)->pos.z = p1.pos.z - 1.0f;
//					//	}
//					//}


//					if (abs(p0.y - p1.y) < 1.0f &&
//						abs(m_manager->getComponent<Components::Velocity>(id0).x) > 0.0f &&
//						abs(p0.z - p1.z) <= abs(p0.x - p1.x))
//					{
//						m_manager->getComponent<Components::Velocity>(id0).x =
//							0.0f;
//						if (p0.x > p1.x)
//						{
//							m_manager->getComponent<Components::Position>(id0).x = p1.x + s1.x;
//						}
//						if (p0.x < p1.x)
//						{
//							m_manager->getComponent<Components::Position>(id0).x = p1.x - s0.x;
//						}
//					}

//					if (abs(p0.y - p1.y) < 1.0f &&
//						abs(m_manager->getComponent<Components::Velocity>(id0).z) > 0.0f &&
//						abs(p0.z - p1.z) >= abs(p0.x-p1.x))
//					{
//						m_manager->getComponent<Components::Velocity>(id0).z =
//							0.0f;
//						if (p0.z > p1.z)
//						{
//							m_manager->getComponent<Components::Position>(id0).z = p1.z + s1.z;
//						}
//						if (p0.z < p1.z)
//						{
//							m_manager->getComponent<Components::Position>(id0).z = p1.z - s0.z;
//						}
//					}
//				}
//			}
//			if (colliderID != 0)
//			{
//				m_manager->getComponent<Components::OnGround>(0) = false;
//			}
//			colliderID = 0;
//			m_receivedEvents.clear();

			stopClock();
		}
	}
}
