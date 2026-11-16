#ifndef Cosmo_SYSTEM_H
#define Cosmo_SYSTEM_H

#include "../Forward.h"
#include "SFML/System/Clock.hpp"
#include <iostream>
#include <string>

namespace Cosmo
{

class World;

inline SystemID
getSystemID()
{
    static SystemID lastID = 0;
    return ++lastID;
}

template<typename T>
inline SystemID
getSystemTypeID() noexcept
{
    static SystemID typeID = getSystemID();
    return typeID;
}

class World;

class System
{
public: //methods

    System();

    virtual void init(World *world) = 0;

    static void updateTimes(float deltaTime);

    void update();

    virtual ~System();

protected: //methods

    virtual void onUpdate() = 0;

    void printAvgTime();

    void startClock();

    void stopClock();

protected: //variables

    static float m_deltaTime;
    static float m_elapsedTime;
    ComponentBitset *m_componentBitset;
    World           *m_world;
    sf::Clock       *m_clock;
    float       m_totalFrameTime;
    float       m_maxFrameTime;
    float       m_minFrameTime;
    float       m_totalFrames;
    std::string m_name;
};

} //namespace Cosmo

#endif //Cosmo_SYSTEM_H
