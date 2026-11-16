#include "PlayerSpawner.h"

#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/OnGroundComponent.h"
#include "../Components/ColorComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/ForwardComponent.h"
#include "../Components/RotationComponent.h"
#include "../Components/ScaleComponent.h"

#include <iostream>
namespace Cosmo
{

namespace Spawner
{

void PlayerSpawner::init(ComponentPoolManager* manager)
{
	m_manager = manager;
}

void PlayerSpawner::spawn()
{
	std::cout << "spawn player" << std::endl;
    EntityID id = m_manager->createNewEntity();
	std::cout << "Created entity: " << id << std::endl;

    m_manager->addComponent<Components::Position>(id).set(0.0f,50.0f,0.0f);
	std::cout << "after position creation" << std::endl;
	m_manager->addComponent<Components::Velocity>(id).set(0.0f,0.0f,0.0f);

	m_manager->addComponent<Components::Forward>(id).set(0.0f,0.0f,-1.0f);
	
	m_manager->addComponent<Components::Rotation>(id);
	m_manager->getComponent<Components::Rotation>(id).fromEulerAngles(0, 0, 0);

	m_manager->addComponent<Components::OnGround>(id) = false;

	m_manager->addComponent<Components::Color>(id).set(0.9f,0.5f,0.1f);

	m_manager->addComponent<Components::Collider>(id);
	m_manager->getComponent<Components::Collider>(id).aabb.pos = glm::vec3({ 0,50,0 });
	m_manager->getComponent<Components::Collider>(id).aabb.size = glm::vec3({ 1,2,1 });

	m_manager->addComponent<Components::Scale>(id);
	m_manager->getComponent<Components::Scale>(id).set(1.0f, 2.0f, 1.0f);

	m_manager->finalizeEntity(id);
}

} //namespace EntitySpawners

} //namespace Cosmo
