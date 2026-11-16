#ifndef Cosmo_DATAMANAGER_H
#define Cosmo_DATAMANAGER_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <unordered_map>
#include <set>

#include "../Forward.h"
#include "../Constants.h"
#include "../Components/CameraComponent.h"
#include "../Components/ViewComponent.h"
#include "../Terrain/Chunk.h"
#include "Pool.h"
#include <omp.h>

namespace BitsetHelper
{
template<typename T, typename... Targs>
struct Helper;

template<typename T>
struct Helper<T>
{
    static void sub(std::bitset<Cosmo::maxComponents>* bits)
    {
        bits->set(Cosmo::getComponentTypeID<T>());
    }
};

template<typename T, typename... Targs>
struct Helper
{
    static void sub(std::bitset<Cosmo::maxComponents>* bits)
    {
        Helper<T>::sub(bits);
        Helper<Targs...>::sub(bits);
    }
};
}

template<typename... Targs>
std::bitset<Cosmo::maxComponents>* getComponentBitset()
{
    std::bitset<Cosmo::maxComponents>* bits = new std::bitset<Cosmo::maxComponents>();

    BitsetHelper::Helper<Targs...>::sub(bits);

    return bits;
}


namespace Cosmo
{

class ComponentPoolManager
{
public:
    ComponentPoolManager();

    ComponentPoolManager(const ComponentPoolManager &) = delete;

    EntityID createNewEntity();

    template<typename T>
    void initPool()
    {
        ComponentID id = getComponentTypeID<T>();
        Pool<T, maxEntities>* p = new Pool<T, maxEntities>(T());
        std::unique_ptr<Pool<T, maxEntities> > uPtr{ p };
        componentPoolsArray[id] = p;
        componentPools.emplace_back(std::move(uPtr));
        ++m_poolCount;
    }

    void removeEntity(EntityID id, std::map<EntityID, EntityID>* map);


    template <typename T>
    void removeComponent(EntityID id)
    {
        entitiesHasPool->getObject(id).reset(getComponentTypeID<T>());
        std::cout << "Component removed" << std::endl;
    }

    //template <typename T>
    void restoreComponentPool(std::map<EntityID, EntityID>* map)
    {
        for (unsigned int i = 0; i < m_poolCount; ++i)
        {
            componentPoolsArray[i]->restore(map);
        }
    }

    void restoreHasPool(std::map<EntityID, EntityID>* map)
    {
        entitiesHasPool->restore(map);
    }

    template<typename T>
    T& addComponent(EntityID id)
    {
        if (!(entitiesHasPool->getObject(id).test(getComponentTypeID<T>())))
        {
            static_cast<Pool<T, maxEntities>*>(componentPoolsArray[getComponentTypeID<T>()])->createObject(id);
            entitiesHasPool->getObject(id).set(getComponentTypeID<T>());
        }
        return getComponent<T>(id);
    }

    void finalizeEntity(EntityID id)
    {
        //for each substring in bitset of entity, create entry in set of systems

        ComponentBitset& bits = entitiesHasPool->getObject(id);

        std::unordered_map<std::bitset<maxComponents>, EntitySet* >::iterator it = m_componentToEntityList.begin();
        for (; it != m_componentToEntityList.end(); ++it)
        {
            if ((it->first & bits) == it->first)
            {
                it->second->insert(id);
            }
        }
    }

    template<typename T>
    T& getComponent(EntityID id)
    {
        return static_cast<Pool<T, maxEntities>*>(componentPoolsArray[getComponentTypeID<T>()])->getObject(id);
    }

    template<typename T>
    bool hasComponent(EntityID id)
    {
        return entitiesHasPool->getObject(id).test(getComponentTypeID<T>());
    }

    template <typename T>
    T* getDataPointer()
    {
        return static_cast<Pool<T, maxEntities>*>(componentPoolsArray[getComponentTypeID<T>()])->getDataPointer();
    }



    //template<typename T>
    //void getEntitySet_sub_impl(std::bitset<maxComponents>* componentBitset)
    //{
    //	componentBitset->set(getComponentTypeID<T>());
    //}

    //template<typename... componentTypes>
    //void getEntitySet_sub(std::bitset<maxComponents>* componentBitset);

    //template<typename T, typename... V>
    //void getEntitySet_sub_helper(std::bitset<maxComponents>* componentBitset)
    //{
    //	getEntitySet_sub_impl<T>();
    //	getEntitySet_sub<V...>(componentBitset);
    //}

    //template<typename... componentTypes>
    //void getEntitySet_sub(std::bitset<maxComponents>* componentBitset)
    //{
    //	getEntitySet_sub_helper<componentTypes...>(componentBitset);
    //}

    template<typename... componentTypes>
    EntitySet* getEntitySet()
    {
        std::bitset<maxComponents>* bits = getComponentBitset<componentTypes...>();

        std::cout << bits->to_string() << std::endl;
        EntitySet* s = nullptr;
        if (m_componentToEntityList.find(*bits) != m_componentToEntityList.end())
        {
            s = m_componentToEntityList.at(*bits);
        }
        delete bits;
        return s;
    }

    EntitySet* getEntitySet(std::bitset<maxComponents>* bits)
    {
        if (m_componentToEntityList.find(*bits) != m_componentToEntityList.end())
        {
            return m_componentToEntityList.at(*bits);
        }
        return nullptr;
    }

    template<typename... Ts>
    std::bitset<maxComponents>* initComponentBitset()
    {
        std::bitset<maxComponents>* bits = getComponentBitset<Ts...>();
        std::cout << bits->to_string() << std::endl;
        m_componentToEntityList.insert(std::make_pair(*bits, new EntitySet()));
        return bits;
    }

private:

    EntityID m_count;
    unsigned int m_poolCount;

    std::unique_ptr<Pool<std::bitset<maxComponents>, maxEntities> > entitiesHasPool;

    std::unordered_map<std::bitset<maxComponents>, EntitySet* > m_componentToEntityList;

    std::array<BasePool*, maxComponents> componentPoolsArray;
    std::vector<std::unique_ptr<BasePool> > componentPools;

};
} //namespace EntityComponentSystem

#endif //Cosmo_DATAMANAGER_H
