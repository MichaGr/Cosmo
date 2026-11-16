#ifndef Cosmo_COMPONENT_H
#define Cosmo_COMPONENT_H

#include "../Forward.h"

namespace Cosmo
{

inline ComponentID getComponentID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentID();
    return typeID;
}

struct Component {
	template<typename... TArgs>
	void set(TArgs&&... FArgs) {}
};

} //namespace Cosmo

#endif //Cosmo_COMPONENT_H
