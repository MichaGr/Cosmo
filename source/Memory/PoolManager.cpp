#include "PoolManager.h"

namespace Cosmo
{

ComponentPoolManager::ComponentPoolManager()
{
	entitiesHasPool = std::make_unique<Pool<std::bitset<maxComponents>, maxEntities> >(std::bitset<maxComponents>());

	//pingPongPositionPool = std::make_unique<PingPongPool<Components::Position> >();
    m_count = 0;
	m_poolCount = 0;
}

EntityID ComponentPoolManager::createNewEntity()
{
	return m_count++;
}

void ComponentPoolManager::removeEntity(EntityID id, std::map < EntityID, EntityID>* map)
{
	--m_count;
	map->insert({ m_count,id });
}

} //namespace Cosmo
