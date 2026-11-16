#include "PhysicsSystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/OnGroundComponent.h"

#include "../Memory/PoolManager.h"

#include <iostream>
#include <omp.h>
#include <bullet/btBulletDynamicsCommon.h>
namespace Cosmo
{

namespace Systems
{

void PhysicsSystem::init(World* manager)
{
//    m_manager = manager;
//    m_componentBitset = m_manager->initComponentBitset<Components::Position, Components::Velocity, Components::OnGround>();
}

void PhysicsSystem::onUpdate()
{

//    for (auto id : *m_manager->getEntitySet(m_componentBitset))
//    {
//        m_manager->getComponent<Components::Position>(id) +=
//                m_manager->getComponent<Components::Velocity>(id) * m_deltaTime;
//        m_manager->getComponent<Components::Position>(id).w = 1.0f;

//        if (!m_manager->getComponent<Components::OnGround>(id))
//        {
//            m_manager->getComponent<Components::Velocity>(id).y -= 9.81 * m_deltaTime;
//        }

//        Components::Velocity& v = m_manager->getComponent<Components::Velocity>(id);

//        if (abs(v.x) > 0.0f ||
//            abs(v.z) > 0.0f)
//        {
//            v.x *= (80.0f * m_deltaTime);
//            v.z *= (80.0f * m_deltaTime);
//        }
//    }

}

PhysicsSystem::~PhysicsSystem()
{}

} //namespace Systems

} //namespace Cosmo
