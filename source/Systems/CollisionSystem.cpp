#include "CollisionSystem.h"
#include <math.h>
#include "../Memory/PoolManager.h"
#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/ColliderComponent.h"
#include "../EventManager/Events/CollisionEvent.h"

namespace Cosmo
{
	namespace Systems
	{
        void CollisionSystem::init(World* world)
		{
            m_world = world;
		}

        void CollisionSystem::onUpdate()
		{
			startClock();

			//check for collisions

//			std::vector<Terrain::Chunk*> chunks = m_manager->getChunksInRadius(m_manager->getComponent<Components::Position>(0), 1);


//			for (unsigned int i = 0; i < chunks.size(); ++i)
//			{
//				std::vector<EntityID>* ids = chunks.at(i)->getBlockIds();
//				for (unsigned int j = 0; j < ids->size(); ++j)
//				{
//					if (collideAABB(0, ids->at(j)))
//					{
//						m_queue->queueEvent(new Events::Collision(0, ids->at(j)));
//					}
//				}
//			}
			//for (unsigned int j = 1; j < m_manager->getEntityCount();++j)
			//{
			//	EntityID id1 = j;
			//	if (m_manager->hasComponent<Components::Collider>(id1))
			//	{
			//		if (collideAABB(0, id1))
			//		{
			//			m_queue->queueEvent(new Events::Collision(0, id1));
			//		}
			//	}
			//}	

			stopClock();
		}

		bool CollisionSystem::collideAABB(unsigned int id0, unsigned int id1)
		{
//			Components::Collider::AABB pos1 = m_manager->getComponent<Components::Collider>(id0).aabb;
//			Components::Collider::AABB pos2 = m_manager->getComponent<Components::Collider>(id1).aabb;

//			return (pos1.pos.x + pos1.size.x > pos2.pos.x &&
//				pos1.pos.x < pos2.pos.x + pos2.size.x &&
//				pos1.pos.y + pos1.size.y > pos2.pos.y &&
//				pos1.pos.y < pos2.pos.y + pos2.size.y &&
//				pos1.pos.z + pos1.size.z > pos2.pos.z &&
//				pos1.pos.z < pos2.pos.z + pos2.size.z);
            return false;
		}

		bool CollisionSystem::collideOBB(float deltaTime, unsigned int id0, unsigned int id1)
		{
			return false;
		}

		bool CollisionSystem::getSeperatingPlane(const glm::vec3& RPos, const glm::vec3& plane, const OBB& box1, const OBB& box2)
		{
//			return (fabs(glm::dot(RPos,plane)) >
//				(fabs(glm::dot((box1.AxisX*box1.Half_size.x),plane)) +
//					fabs(glm::dot((box1.AxisY*box1.Half_size.y),plane)) +
//					fabs(glm::dot((box1.AxisZ*box1.Half_size.z),plane)) +
//					fabs(glm::dot((box2.AxisX*box2.Half_size.x),plane)) +
//					fabs(glm::dot((box2.AxisY*box2.Half_size.y),plane)) +
//					fabs(glm::dot((box2.AxisZ*box2.Half_size.z),plane))));
            return false;
		}
	}
}
