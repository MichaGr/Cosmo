#ifndef COMPONENTPOOL_H
#define COMPONENTPOOL_H

#include "../Forward.h"
#include "BasePool.h"
#include "Pool.h"
#include <iostream>
namespace Cosmo
{

	template <typename T>
	class ComponentPool : public BasePool
	{
	public:
		ComponentPool()
		{
			m_dataPool = new Pool<T, maxEntities>(T());
			m_permutationPool = new Pool<EntityID, maxEntities>(undefinedID);
			m_inversePool = new Pool<ComponentID, maxEntities>(undefinedID);
		}
		~ComponentPool()
		{
			delete m_dataPool;
			delete m_permutationPool;
			delete m_inversePool;
		}

		void add(EntityID id)
		{
			ComponentID cID = m_dataPool->createObject();
			m_permutationPool->getObject(id) = cID;
			m_inversePool->getObject(cID) = id;
		}

		void remove(EntityID id)
		{
			m_dataPool->removeObject(m_permutationPool->getObject(id));
			//m_permutationPool->removeObject(id);
		}

		T* getComponent(EntityID id)
		{
			return &m_dataPool->getObject(id);
		}

		bool hasComponent(EntityID id)
		{
			return m_permutationPool->getObject(id) != undefinedID;
		}

		T* getDataPointer()
		{
			return m_dataPool->getDataPointer();
		}

		EntityID* getPermutationPointer()
		{
			return m_permutationPool->getDataPointer();
		}

		void compress()
		{
			std::map<unsigned int, unsigned int>* map = new std::map<unsigned int, unsigned int>();
			m_dataPool->compress(map);
			std::map<unsigned int, unsigned int>::iterator map_it = map->begin();
			std::cout << "Data Pool compressed" << std::endl;
			for (; map_it != map->end(); ++map_it)
			{
				m_permutationPool->getObject(m_inversePool->getObject(map_it->first)) = map_it->second;
			}

			std::cout << "Permutation restored" << std::endl;
			//m_permutationPool->compress();
			//std::cout << "Permutation compressed" << std::endl;
			////restore m_inversePool todo
			//for (unsigned int i = 0; i < m_permutationPool->count(); ++i)
			//{
			//	m_inversePool->getObject(m_permutationPool->getObject(i)) = i;
			//}
			//std::cout << "InversePermutation restored" << std::endl;
			delete map;
		}

	private:
		void restoreInversePermutation()
		{}

		Pool<T, maxEntities>* m_dataPool;
		Pool<EntityID, maxEntities>* m_permutationPool;
		Pool<ComponentID, maxEntities>* m_inversePool;
	};

}
#endif //COMPONENTPOOL_H