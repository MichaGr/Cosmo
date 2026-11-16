#ifndef Cosmo_PLAYERSPAWNER_H
#define Cosmo_PLAYERSPAWNER_H

#include "EntitySpawner.h"

namespace Cosmo
{

namespace Spawner
{

class PlayerSpawner : public EntitySpawner
{
public:
	PlayerSpawner() {}
    PlayerSpawner(const PlayerSpawner&) = delete;

    void init(ComponentPoolManager* manager) override;
    void spawn() override;
    ~PlayerSpawner() override {}

private:
	ComponentPoolManager* m_manager;

};

} //namespace EntitySpawners

} //namespace Cosmo

#endif //Cosmo_PLAYERSPAWNER_H
