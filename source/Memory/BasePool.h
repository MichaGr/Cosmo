#ifndef BASEPOOL_H
#define BASEPOOL_H

#include <map>
#include "../Forward.h"

class BasePool
{
public:
    virtual ~BasePool();

    virtual void restore(std::map<Cosmo::EntityID, Cosmo::EntityID>* map) = 0;
};

#endif //BASEPOOL_H
