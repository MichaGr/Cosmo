#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Cosmo
{

	constexpr unsigned int maxComponents = 32;
	constexpr unsigned int maxSystems = 32;
	constexpr unsigned int maxEntities = 1024 * 1024;
    constexpr int undefinedID = -1;
	constexpr int border = (1 << 30) - (1 << 10);
	constexpr int chunkSize = 16;
	//constexpr int border = 128;
} //namespace Cosmo

#endif
