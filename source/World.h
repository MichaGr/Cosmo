#ifndef Cosmo_WORLD_H
#define Cosmo_WORLD_H

#include <memory>
#include <bitset>
#include <vector>

#include "Forward.h"
#include "Constants.h"

#include "Memory/PoolManager.h"
#include "Systems/System.h"
#include "Systems/RenderSystem.h"

#include "GL/glew.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EntitySpawner/TerrainSpawner.h"
#include "EntitySpawner/PlayerSpawner.h"
#include "EventManager/EventQueue.h"

namespace Cosmo
{

class World
{
public:

    World();

    ~World();

    World(const World &) = delete;

    template<typename T>
    void initComponentPool()
    {
        m_manager->initPool<T>();
    }

    template<typename T, typename... TArgs>
    SystemID addSystem(std::size_t initPriority,
                       std::size_t updatePriority,
                       TArgs &&... mArgs)
    {
        if (m_systemsBitSet[getSystemTypeID<T>()])
        {
            return -1;
        }

        T *s(new T(std::forward<TArgs>(mArgs)...));
        std::unique_ptr<System> uPtr{s};
        m_systems.emplace_back(std::move(uPtr));

        m_systemsBitSet[getSystemTypeID<T>()] = true;
        m_systemsArray[getSystemTypeID<T>()]  = s;
        m_initPriority[initPriority]          = getSystemTypeID<T>();
        m_updatePriority[updatePriority]      = getSystemTypeID<T>();
        ++m_countSystems;
        return getSystemTypeID<T>();
    }

    void init(sf::RenderWindow *window);

    void update(float deltaTime);

    void render();

    inline bool isRunning()
    { return m_running; }

    EventQueue *getEventQueue()
    { return m_eventQueue.get(); }



    //---TODO

    inline Components::Camera *getCamera()
    {
        return m_camera.get();
    }

    inline Components::View *getView()
    {
        return m_view.get();
    }


    inline void kill()
    {
        m_running = false;
    }

    Terrain::Chunk &getChunk(std::pair<int, int> &pos)
    {
        return m_chunks.at(pos);
    }

    std::vector<Terrain::Chunk *> getChunksInRadius(const glm::vec3 &pos,
                                                    int radius)
    {
        std::vector<Terrain::Chunk *> ret;

        int x = int(pos.x) / Cosmo::chunkSize;
        int z = int(pos.z) / Cosmo::chunkSize;

        std::pair<int, int> p = std::make_pair(x, z);

        for (int i = x - radius; i <= x + radius; ++i)
        {
            for (int j = z - radius; j <= z + radius; ++j)
            {
                p.first  = i;
                p.second = j;

                if (m_chunks.find(p) != m_chunks.end())
                {
                    ret.push_back(&m_chunks.find(p)
                                           ->second);
                }
            }
        }

        return ret;
    }

    std::map<std::pair<int, int>, Terrain::Chunk>::iterator getChunkBegin()
    {
        return m_chunks.begin();
    }

    std::map<std::pair<int, int>, Terrain::Chunk>::iterator getChunkEnd()
    {
        return m_chunks.end();
    }

    void addChunk(std::pair<int, int> pos)
    {
        if (m_chunks.find(pos) == m_chunks.end())
        {
            m_chunks.insert(std::make_pair(pos, Terrain::Chunk(glm::ivec3({pos.first, 0, pos.second}))));
        }
    }

    bool isChunkLoaded(std::pair<int, int> pos)
    {
        return m_chunks.find(pos) != m_chunks.end();
    }

    void deleteChunk(std::pair<int, int> &pos)
    {
        Terrain::Chunk &chunk = m_chunks.at(pos);

        std::map<EntityID, EntityID> *map = new std::map<EntityID, EntityID>();

        std::vector<EntityID> *blockIDs = chunk.getBlockIds();
        for (unsigned int i = 0; i < blockIDs->size(); ++i)
        {
            m_manager->removeEntity(blockIDs->at(i), map);
        }

        m_chunks.erase(pos);

        std::map<std::pair<int, int>, Terrain::Chunk>::iterator it = m_chunks.begin();

        for (; it != m_chunks.end(); ++it)
        {
            it->second
              .updateIDs(map);
        }

        //update memory

        m_manager->restoreComponentPool(map);
        m_manager->restoreHasPool(map);

        delete map;
    }

    template<typename... Ts>
    ComponentBitset *initComponentBitset()
    {
        return m_manager->initComponentBitset<Ts...>();
    }

    inline ComponentPoolManager *getManager()
    { return m_manager.get(); }

    inline EntitySet *getEntitySet(ComponentBitset *bitset)
    {
        return m_manager->getEntitySet(bitset);
    }
    //---TODO END

    inline EntityID getPlayerID()
    { return m_player; }

    inline void setPlayerID(EntityID id)
    { m_player = id; }

private:

    bool m_running;

    EntityID m_player;

    std::unique_ptr<Components::Camera> m_camera;
    std::unique_ptr<Components::View>   m_view;


    //TODO Change Terrain::CHunk to EntityID, store chunks as meshed in componentpool

    std::map<std::pair<int, int>, Terrain::Chunk> m_chunks;
    std::map<std::pair<int, int>, EntityID> m_chunkIDs;

    std::unique_ptr<EventQueue> m_eventQueue;

    std::unique_ptr<ComponentPoolManager> m_manager;

    std::vector<std::unique_ptr<System> > m_systems;
    Systems::RenderSystem *m_renderSystem;

    std::bitset<maxSystems>             m_systemsBitSet;
    std::array<System *, maxSystems>    m_systemsArray;
    std::array<std::size_t, maxSystems> m_initPriority;
    std::array<std::size_t, maxSystems> m_updatePriority;

    std::size_t m_countSystems;
};

} //namespace Cosmo

#endif //Cosmo_WORLD_H
