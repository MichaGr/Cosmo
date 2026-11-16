#ifndef CHUNK_H
#define CHUNK_H


#include "../../glm-0.9.9.3/glm/vec2.hpp"
#include "../../glm-0.9.9.3/glm/vec3.hpp"
#include "utils.h"
#include "../Constants.h"
#include "../Forward.h"
#include <unordered_map>
#include <map>
#include <vector>

namespace Terrain
{
	class Chunk
	{
	public:
		Chunk(const glm::ivec3& position)
			: m_id(chunkHash(position)),
			m_position(position)
		{
            m_blockIds.reserve(Cosmo::chunkSize * Cosmo::chunkSize);
		}

		inline unsigned long long getID() const { return m_id; }
		inline glm::ivec3 getPosition() const{ return m_position; }

        inline bool checkSize() { return m_blockIds.size() == Cosmo::chunkSize * Cosmo::chunkSize; }

        std::vector<Cosmo::EntityID>* getBlockIds() { return &m_blockIds; }
        std::pair<Cosmo::EntityID, Cosmo::EntityID> getMemoryBoundaries() { return std::make_pair(m_blockIds.at(0), m_blockIds.at(m_blockIds.size() - 1)); }

        void updateIDs(std::map<Cosmo::EntityID, Cosmo::EntityID>* map);

        void addBlockId(Cosmo::EntityID id);
        void removeBlockId(Cosmo::EntityID id);
	private:
		unsigned long long m_id;
		glm::ivec3 m_position;
        std::vector<Cosmo::EntityID> m_blockIds;
	};
} //namespace Terrain

#endif //CHUNK_H
