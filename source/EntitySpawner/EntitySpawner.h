#ifndef Cosmo_ENTITYSPAWNER_H
#define Cosmo_ENTITYSPAWNER_H

#include "../Forward.h"
#include "../Memory/PoolManager.h"

namespace Cosmo
{

class EntitySpawner
{
public:
    virtual void init(ComponentPoolManager* manager) = 0;
    virtual void spawn() = 0;
    virtual ~EntitySpawner() {}
};

} //namespace Cosmo

#endif