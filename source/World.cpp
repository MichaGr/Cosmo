#include "World.h"

#include "Systems/System.h"
#include "Systems/PhysicsSystem.h"
#include "Components/VelocityComponent.h"
#include "Components/PositionComponent.h"


namespace Cosmo
{

World::World()
{
    m_manager = std::make_unique<ComponentPoolManager>();
	m_countSystems = 0;
	m_eventQueue = std::make_unique<EventQueue>();
    m_camera = std::make_unique<Components::Camera>();
    m_view = std::make_unique<Components::View>();
    m_running = true;
	
}

World::~World()
{
    delete m_renderSystem;
}

void World::init(sf::RenderWindow* window)
{
	for (std::size_t i = 0; i < m_countSystems;++i)
	{
        m_systemsArray[m_initPriority[i]]->init(this);
	}
    m_renderSystem = new Systems::RenderSystem(window);
    m_renderSystem->init(this);
}

void World::update(float deltaTime)
{
	m_eventQueue->broadCast();

    System::updateTimes(deltaTime);
    for (std::size_t i = 0; i < m_countSystems;++i)
	{
        m_systemsArray[m_updatePriority[i]]->update();
	}
}

void World::render()
{
    m_renderSystem->update();
}

} //namespace Cosmo
