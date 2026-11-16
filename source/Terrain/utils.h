#ifndef TERRAINUTILS_H
#define TERRAINUTILS_H

#include "../../glm-0.9.9.3/glm/vec3.hpp"
#include "../Constants.h"

namespace Terrain
{
	inline unsigned long long chunkHash(const glm::ivec3& p)
	{
		return ((unsigned long long)(p.y) << 0) |
			((unsigned long long)(p.x) << 4) |
			((unsigned long long)(p.z) << 34);
	}
}

#endif //TERRAINUTILS_H