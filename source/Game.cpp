#include "Game.h"

#include "Systems/RenderSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/ViewSystem.h"
#include "Systems/CollisionHandlerSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/TerrainSpawnerSystem.h"
#include "Systems/MoveForwardSystem.h"
#include "Systems/UpdateBoundingBoxesSystem.h"

#include "Components/VelocityComponent.h"
#include "Components/ColorComponent.h"
#include "Components/OnGroundComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/ForwardComponent.h"
#include "Components/RotationComponent.h"
#include "Components/ScaleComponent.h"
#include "Components/MeshComponent.h"

#include <iostream>
#include "config.h"
namespace Cosmo
{
	Game::Game()
	{
		m_world = std::make_unique<World>();
		m_running = true;
	}

	Game::~Game()
	{
		std::cout << "Avg FrameTime: " << m_totalFrameTime / m_totalFrames << std::endl;
	}

	void Game::init()
	{
		//init window
		sf::ContextSettings settings;
        settings.majorVersion = OPENGL_MAJOR_VERSION;
        settings.minorVersion = OPENGL_MINOR_VERSION;
        settings.depthBits = DEPTH_BITS;
        settings.stencilBits = STENCIL_BITS;
        settings.antialiasingLevel = ANTIALIASING_LEVEL;
        settings.attributeFlags = sf::ContextSettings::Attribute::Core;
        m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1440, 900),
            "Cosmo",
            sf::Style::Default,
			settings);
//        m_window->setFramerateLimit(FRAME_LIMIT);

		// activate the window
		m_window->setActive(true);

        m_world->initComponentPool<Components::Position>();
        m_world->initComponentPool<Components::Velocity>();
        m_world->initComponentPool<Components::Color>();
        m_world->initComponentPool<Components::OnGround>();
        m_world->initComponentPool<Components::Collider>();
        m_world->initComponentPool<Components::Rotation>();
        m_world->initComponentPool<Components::Forward>();
        m_world->initComponentPool<Components::Scale>();
        m_world->initComponentPool<Components::Mesh>();

//        m_world->initComponentPools<Components::Position,
//                                    Components::Velocity,
//                                    Components::Color,
//                                    Components::OnGround,
//                                    Components::Collider,
//                                    Components::Rotation,
//                                    Components::Forward,
//                                    Components::Scale,
//                                    Components::Mesh>();

//		m_world->addSystem<Systems::CollisionHandlerSystem>(0, 0, m_world->getEventQueue());
//		m_world->addSystem<Systems::PhysicsSystem>(2,2);
        m_world->addSystem<Systems::InputSystem>(0,0,m_window.get());
//		//m_world->addSystem<Systems::MoveForwardSystem>(3, 3);
//		m_world->addSystem<Systems::UpdateBoundingBoxesSystem>(3, 3);
//		m_world->addSystem<Systems::CollisionSystem>(4, 4, m_world->getEventQueue());
        m_world->addSystem<Systems::ViewSystem>(1, 1);
//		m_world->addSystem<Systems::TerrainSpawnerSystem>(6,6);

		this->initGLEW();
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);
		m_world->init(m_window.get());
	}

	void Game::initGLEW()
	{
		glewInit();
	}

	void Game::run()
	{ 
        const float dt = 1.0f / PHYSICS_FRAMERATE;
		m_totalFrameTime = 0.0f;
		m_totalFrames = 0.0f;

		float accumulator = 0.0;

		while (m_world->isRunning())
		{
			float frameTime = clock.getElapsedTime().asSeconds();
			clock.restart();

			accumulator += frameTime;
			m_totalFrameTime += frameTime;
			m_totalFrames += 1.0f;

            while (accumulator >= dt)
            {
                m_world->update(dt);
                accumulator -= dt;
            }

			m_world->render();
		}
	}
}
