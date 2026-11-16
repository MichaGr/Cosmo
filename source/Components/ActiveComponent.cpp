#include "ActiveComponent.h"

namespace Cosmo
{

namespace Components
{

void Active::init()
{
    m_active = true;
}

Active::~Active()
{}

bool Active::isActive() const
{
    return m_active;
}

} //namespace Components

} //namespace Cosmo
