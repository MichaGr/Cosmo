#include "InputSystem.h"
#include "../Memory/PoolManager.h"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Event.hpp"

#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/OnGroundComponent.h"
#include "../Components/ColorComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/RotationComponent.h"
#include "../Components/ForwardComponent.h"


#include "../World.h"
namespace Cosmo
{

	namespace Systems
	{
		InputSystem::InputSystem(sf::RenderWindow *window) : m_window(window)
		{
			m_name = "InputSystem";
		}

		InputSystem::~InputSystem()
		{
			m_window = nullptr;
		}

        void InputSystem::init(World *world)
		{
			std::cout << "init input" << std::endl;
			m_window->setMouseCursorVisible(false);
            m_world = world;
		}

        void InputSystem::onUpdate()
		{
			startClock();
			sf::Event windowEvent;
			while (m_window->pollEvent(windowEvent))
			{
				switch (windowEvent.type)
				{
				case sf::Event::Closed:
                    m_world->kill();
					break;

				case sf::Event::KeyPressed:
					if (windowEvent.key.code == sf::Keyboard::I)
					{

					}

					if (windowEvent.key.code == sf::Keyboard::O)
					{
					}

					if (windowEvent.key.code == sf::Keyboard::Escape)
					{
                        m_world->kill();
					}
					if (windowEvent.key.code == sf::Keyboard::Q)
					{
                        m_world->getCamera()->moveForward(0.1f);

					}

                    if(windowEvent.key.code == sf::Keyboard::B)
                    {
//                        m_world->getB() += 0.001f;
                    }

                    if(windowEvent.key.code == sf::Keyboard::N)
                    {
//                        m_world->getB() -= 0.001f;
                    }
					if (windowEvent.key.code == sf::Keyboard::E)
					{
                        m_world->getCamera()->moveForward(-0.1f);
					}
					if (windowEvent.key.code == sf::Keyboard::A)
					{
                        //m_world->getCamera()->moveRight(-0.1f);
//						playerMoveRight = 1.0f;
                        m_world->getCamera()->position.x += 0.4f;

					}
					if (windowEvent.key.code == sf::Keyboard::D)
					{
                        //m_world->getCamera()->moveRight(0.1f);
//						playerMoveRight = -1.0f;
                        m_world->getCamera()->position.x -= 0.4f;
					}
					if (windowEvent.key.code == sf::Keyboard::W)
					{
                        m_world->getCamera()->position.y += 0.4f;

					}
					if (windowEvent.key.code == sf::Keyboard::S)
					{
                        m_world->getCamera()->position.y -= 0.4f;
					}
					if (windowEvent.key.code == sf::Keyboard::Left)
					{
                        m_world->getCamera()->moveRight(0.1f);
					}
					if (windowEvent.key.code == sf::Keyboard::Right)
					{
                        m_world->getCamera()->moveRight(-0.4f);
					}
					if (windowEvent.key.code == sf::Keyboard::Up)
					{
                        m_world->getCamera()->moveUp(0.4f);
					}
					if (windowEvent.key.code == sf::Keyboard::Down)
					{
					}
					if (windowEvent.key.code == sf::Keyboard::Space)
					{
                        m_world->getCamera()->position += 0.4f * m_world->getCamera()->direction;
					}
					break;
				case sf::Event::KeyReleased:
					if (windowEvent.key.code == sf::Keyboard::A)
					{}
					if (windowEvent.key.code == sf::Keyboard::D)
					{}
					if (windowEvent.key.code == sf::Keyboard::W)
					{}
					if (windowEvent.key.code == sf::Keyboard::S)
					{}
					if (windowEvent.key.code == sf::Keyboard::Down)
					{}
					break;
				case sf::Event::MouseMoved:
					if (m_window->getSize().x / 2 != windowEvent.mouseMove.x)
					{
                        m_world->getCamera()->horizontalAngle -=
                            0.005f * float(1440 / 2 - windowEvent.mouseMove.x);
					}
					if (m_window->getSize().y / 2 != windowEvent.mouseMove.y)
					{
                        m_world->getCamera()->verticalAngle -= 0.005f * float(900 / 2 - windowEvent.mouseMove.y);
					}
					break;

				case sf::Event::MouseWheelScrolled:
                    m_world->getCamera()->zoom += windowEvent.mouseWheelScroll.delta * 0.03f;
				case sf::Event::JoystickButtonPressed:
					//A
					if (windowEvent.joystickButton.button == 0)
					{
                        if (!m_world->getManager()->getComponent<Components::OnGround>(0).set)
						{
                            m_world->getManager()->getComponent<Components::Velocity>(0).y += 0.1f;
                            m_world->getManager()->getComponent<Components::OnGround>(0) = false;
						}
					}
					//B
					if (windowEvent.joystickButton.button == 1)
					{
					}
					//X
					if (windowEvent.joystickButton.button == 2)
					{
					}
					//Y
					if (windowEvent.joystickButton.button == 3)
					{
					}
					//LB
					if (windowEvent.joystickButton.button == 4)
					{
					}
					//RB
					if (windowEvent.joystickButton.button == 5)
					{
					}
					//Start
					if (windowEvent.joystickButton.button == 6)
					{
					}
					//Select
					if (windowEvent.joystickButton.button == 7)
					{
					}
					//L3
					if (windowEvent.joystickButton.button == 8)
					{
					}
					//R3
					if (windowEvent.joystickButton.button == 9)
					{
					}
					break;

				case sf::Event::JoystickButtonReleased:
					std::cout << std::endl;

				case sf::Event::JoystickMoved:
					if (windowEvent.joystickMove.axis == sf::Joystick::PovX)
					{}
					if (windowEvent.joystickMove.axis == sf::Joystick::PovY)
					{}
					break;
				}

			}
            sf::Mouse::setPosition(sf::Vector2i(1440 / 2, 900 / 2), *m_window);
//			m_world->getCamera()->horizontalAngle += horizontal;

//			m_world->getCamera()->verticalAngle += vertical;
//			m_world->getCamera()->moveUp(camUp);
//			m_world->getComponent<Components::Velocity>(0).x += playerMoveUp * m_world->getComponent<Components::Forward>(0).x;
//			m_world->getComponent<Components::Velocity>(0).z += playerMoveUp * m_world->getComponent<Components::Forward>(0).z;

//			horizontal = 0.0f;
			stopClock();
		}

	}
}
