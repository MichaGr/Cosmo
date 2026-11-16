#include "System.h"

namespace Cosmo
{

float System::m_deltaTime = 0.0f;
float System::m_elapsedTime = 0.0f;

System::System()
{
    m_clock = new sf::Clock();
    m_totalFrameTime = 0.0;
    m_totalFrames = 0.0;
    m_maxFrameTime = 0.0;
    m_minFrameTime = 0.0;
}

System::~System()
{
    printAvgTime();
    delete m_clock;
    delete m_componentBitset;
}

void System::printAvgTime()
{
    std::cout << m_name << ": ";
    std::cout << "avg: " << m_totalFrameTime / m_totalFrames;
    std::cout << " min: " << m_minFrameTime << " max: " << m_maxFrameTime << std::endl;
}

void System::startClock()
{
    m_clock->restart();
}

void System::stopClock()
{
    float f = float(m_clock->getElapsedTime().asSeconds());

    //start after 10 frames
    if (m_totalFrames < 10.0f)
    {
        m_maxFrameTime = f;
        m_minFrameTime = f;
    }
    else
    {
        m_maxFrameTime = f > m_maxFrameTime ? f : m_maxFrameTime;
        m_minFrameTime = f < m_minFrameTime ? f : m_minFrameTime;
    }
    m_totalFrames += 1.0f;
    m_totalFrameTime += m_clock->getElapsedTime().asSeconds();
}

void System::update()
{
        startClock();
        onUpdate();
        stopClock();
}

void System::updateTimes(float deltaTime)
{
    m_deltaTime = deltaTime;
    m_elapsedTime += deltaTime;
}

}
