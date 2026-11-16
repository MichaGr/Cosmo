#include "Chunk.h"

namespace Terrain
{
    void Chunk::addBlockId(Cosmo::EntityID id)
	{
		m_blockIds.push_back(id);
	}

    void Chunk::removeBlockId(Cosmo::EntityID id)
	{
		return;
	}

    void Chunk::updateIDs(std::map<Cosmo::EntityID, Cosmo::EntityID> *map)
	{
		for (unsigned int i = 0; i < m_blockIds.size(); ++i)
		{
			if (map->find(m_blockIds.at(i)) != map->end())
			{
				m_blockIds.at(i) = map->at(m_blockIds.at(i));
			}
		}
	}
}
