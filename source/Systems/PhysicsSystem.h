#ifndef Cosmo_PHYSICSSYSTEM_H
#define Cosmo_PHYSICSSYSTEM_H

#include "System.h"

namespace Cosmo
{

namespace Systems
{

class PhysicsSystem : public System
{
public:
	PhysicsSystem() { m_name = "PhysicsSystem"; }
    void init(World* world) override;
    void onUpdate() override;
    ~PhysicsSystem() override;
};

} //namespace Systems

} //namespace Cosmo

#endif //Cosmo_PHYSICSSYSTEM_H
