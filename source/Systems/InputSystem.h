#ifndef ENTITYCOMPONENTSYTEM_INPUTSYSTEM_H
#define ENTITYCOMPONENTSYTEM_INPUTSYSTEM_H

#include "System.h"
#include <SFML/Graphics/RenderWindow.hpp>


namespace Cosmo
{

namespace Systems
{

class InputSystem
        : public System
{
public: //methods

    explicit InputSystem(sf::RenderWindow *window);

    void init(World *world) override;

    void onUpdate() override;

    ~InputSystem() override;

private: //variables

    sf::RenderWindow *m_window;
};

} //namespace Systems
} //namespace Cosmo

#endif //ENTITYCOMPONENTSYTEM_INPUTSYSTEM_H
