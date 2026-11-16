#ifndef TERRAINSPAWNERSYSTEM_H
#define TERRAINSPAWNERSYSTEM_H

#include "System.h"
#include "../EntitySpawner/TerrainSpawner.h"
#include "../EntitySpawner/PlayerSpawner.h"
#include "../Terrain/Chunk.h"
#include <map>
#include <vector>
#include <queue>

namespace Cosmo
{

namespace Systems
{
class TerrainSpawnerSystem
        : public System
{
public: //methods

    TerrainSpawnerSystem();

    ~TerrainSpawnerSystem() override;

    void init(World *world) override;

    void onUpdate() override;

private: //methods

    bool updatePlayerPosition();

    bool updatePlayerChunkPosition();

    void queueChunksForLoading();

    void queueChunksForDeleting();

    void deleteChunk();

private: //variables

    Spawner::TerrainSpawner *m_terrainSpawner;
    Spawner::PlayerSpawner  *m_playerSpawner;
    int size;

    std::map<std::pair<int, int>, Terrain::Chunk> m_chunkLoaded;
    std::queue<glm::ivec3>                        m_queueChunks;
    std::queue<glm::ivec3>                        m_queueDeleteChunks;

    glm::ivec3 m_oldPlayerPosition;
    glm::ivec3 m_oldPlayerChunkPosition;
    int        m_radius;

};

} //namespace Systems
} //namespace Cosmo

#endif //TERRAINSPAWNERSYSTEM_H
