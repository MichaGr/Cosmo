#ifndef ENTITYCOMPONETSYSTEM_FORWARD_H
#define ENTITYCOMPONETSYSTEM_FORWARD_H

#include "Constants.h"
#include <cstddef>
#include <set>
#include <bitset>


namespace Cosmo
{

using cInt = int;
using cUInt = unsigned int;
using cLong = long;
using cULong = unsigned long;
using cReal = float;

using vec3 = cReal[3];
using vec4 = cReal[4];
using mat3x3 = cReal[9];
using mat4x4 = cReal[16];


using ID = int;
using EntityID = ID;
using ComponentID = ID;
using SystemID = ID;
using SystemPriority = int;
using EntitySet = std::set<EntityID>;
using ComponentBitset = std::bitset<maxComponents>;

} //namespace Cosmo

#endif //ENTITYCOMPONETSYSTEM_FORWARD_H
