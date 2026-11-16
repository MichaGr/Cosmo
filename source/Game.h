#ifndef Cosmo_GAME_H
#define Cosmo_GAME_H

#include <memory>

#include "World.h"
#include "SFML/System/Clock.hpp"

namespace Cosmo
{

class Game
{
public: //methods
    Game();

    ~Game();

    void init();

    void run();


private: //methods
    void initGLEW();

private: //variables
    std::unique_ptr<World>            m_world;
    bool                              m_running;
    std::unique_ptr<sf::RenderWindow> m_window;
    sf::Clock                         clock;

    float m_totalFrameTime;
    float m_totalFrames;
};

} //namespace Cosmo

#endif //Cosmo_GAME_H