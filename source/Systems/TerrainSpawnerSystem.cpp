#include "TerrainSpawnerSystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/ColorComponent.h"
#include "../Constants.h"
#include <math.h>
#include <omp.h>

#include "../World.h"

namespace Cosmo
{
namespace Systems
{

TerrainSpawnerSystem::TerrainSpawnerSystem()
        : m_terrainSpawner(nullptr),
          m_playerSpawner(nullptr),
          size(16),
          m_radius(5),
          m_oldPlayerChunkPosition(glm::ivec3(0,0,0)),
          m_oldPlayerPosition(glm::ivec3(0,0,0))

{
    m_name = "TerrainSpawnerSystem";
}

TerrainSpawnerSystem::~TerrainSpawnerSystem()
{
    delete m_terrainSpawner;
    delete m_playerSpawner;
}

void
TerrainSpawnerSystem::init(World* world)
{
    m_chunkLoaded.clear();
    m_world = world;

    m_radius = 5;


    //queue chunks initially

    for (int r = 0; r <= m_radius; ++r)
    {
        for (int x = -r; x <= r; ++x)
        {
            for (int z = -r; z <= r; ++z)
            {
                if (abs(x) == r || abs(z) == r)
                {
                    m_queueChunks.push(glm::ivec3({x + m_oldPlayerChunkPosition.x, 0, z + m_oldPlayerChunkPosition.z}));
                }
            }
        }
    }


    m_terrainSpawner = new Spawner::TerrainSpawner;
//            m_terrainSpawner->init(m_world);

    m_playerSpawner = new Spawner::PlayerSpawner;
//            m_playerSpawner->init(m_world);
    m_playerSpawner->spawn();


    Components::Position& playerPosition = m_world->getManager()
                                                  ->getComponent<Components::Position>(0);

    m_oldPlayerPosition      = playerPosition;
    m_oldPlayerChunkPosition = m_oldPlayerPosition / chunkSize;
}

void
TerrainSpawnerSystem::onUpdate()
{
    if (updatePlayerChunkPosition())
    {
        queueChunksForDeleting();
        queueChunksForLoading();
    }

    if (!m_queueDeleteChunks.empty())
    {
        this->deleteChunk();
    }

    if (!m_queueChunks.empty())
    {
        glm::ivec3 next = m_queueChunks.front();

        m_world->addChunk(std::make_pair(next.x, next.z));
        std::pair<int, int> p = std::make_pair(next.x, next.z);
        Terrain::Chunk& nextChunk      = m_world->getChunk(p);
        auto          & playerPosition = m_world->getManager()
                                                ->getComponent<Components::Position>(0);

        int dist       = std::max(std::abs(next.x - (int) playerPosition.x), std::abs(next.z - (int) playerPosition.x));
        int resolution = 1;
        m_terrainSpawner->setParameters(&nextChunk, resolution);
        m_terrainSpawner->spawn();

        m_queueChunks.pop();
    }
}

bool
TerrainSpawnerSystem::updatePlayerPosition()
{
    auto& playerPosition = m_world->getManager()
                                  ->getComponent<Components::Position>(0);

    if (m_oldPlayerPosition.x != (int) playerPosition.x ||
        m_oldPlayerPosition.y != (int) playerPosition.y ||
        m_oldPlayerPosition.z != (int) playerPosition.z)
    {
        m_oldPlayerPosition.x = (int) playerPosition.x;
        m_oldPlayerPosition.y = (int) playerPosition.y;
        m_oldPlayerPosition.z = (int) playerPosition.z;

        return true;
    }

    return false;
}

bool
TerrainSpawnerSystem::updatePlayerChunkPosition()
{
    if (updatePlayerPosition())
    {
        if (m_oldPlayerChunkPosition != m_oldPlayerPosition / chunkSize)
        {
            m_oldPlayerChunkPosition = m_oldPlayerPosition / chunkSize;
            return true;
        }
    }
    return false;
}

void
TerrainSpawnerSystem::queueChunksForLoading()
{
    if (m_queueChunks.empty())
    {
        //Create queue to check

        std::queue<glm::ivec3> q;

        for (int r = 0; r <= m_radius; ++r)
        {
            for (int x = -r; x <= r; ++x)
            {
                for (int z = -r; z <= r; ++z)
                {
                    if (abs(x) == r || abs(z) == r)
                    {
                        q.push(glm::ivec3({x + m_oldPlayerChunkPosition.x, 0, z + m_oldPlayerChunkPosition.z}));

                    }
                }
            }
        }

        //check if chunk is already loaded in map
        while (!q.empty())
        {
            glm::ivec3 next = q.front();

            if (!m_world->isChunkLoaded(std::make_pair(next.x, next.z)))
            {
                m_queueChunks.push(next);
            }
            q.pop();
        }

    }
}

void
TerrainSpawnerSystem::deleteChunk()
{
    glm::ivec3 chunkPosition = m_queueDeleteChunks.front();

    std::pair<int, int> p = std::make_pair(chunkPosition.x, chunkPosition.z);
    m_world->deleteChunk(p);
    m_queueDeleteChunks.pop();
}

void
TerrainSpawnerSystem::queueChunksForDeleting()
{
    if (m_queueDeleteChunks.empty())
    {
        auto it = m_world->getChunkBegin();
        for (; it != m_world->getChunkEnd(); ++it)
        {
            int x = abs(it->second
                          .getPosition()
                          .x - m_oldPlayerChunkPosition.x);
            int z = abs(it->second
                          .getPosition()
                          .z - m_oldPlayerChunkPosition.z);
            x = x > z ? x : z;
            if (x > m_radius)
            {
                m_queueDeleteChunks.push(it->second
                                           .getPosition());
            }
        }
    }
}
}
}
