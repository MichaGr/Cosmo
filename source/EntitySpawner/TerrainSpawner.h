#ifndef TERRAINSPAWNER_H
#define TERRAINSPAWNER_H

#include "EntitySpawner.h"
#include "../Math/Noise/PerlinNoise.h"
#include "../Terrain/Chunk.h"
#include "../Terrain/ChunkMeshCreator.h"
#include "../World.h"

namespace Cosmo
{
namespace Spawner
{
class TerrainSpawner
        : public EntitySpawner
{
public: //methods

    void init(World *manager) override;

    void spawn() override;

    ~TerrainSpawner() override
    {}

    void setParameters(Terrain::Chunk *chunk,
                       int resolution);

private: //methods

    double remap(double chunkID,
                 double blockID,
                 double c,
                 double b_cp);

    double value(double chunkPositionX,
                 double chunkPositionZ,
                 double x,
                 double z);

private: //variables

    World* m_world;
    MathLib::PerlinNoise generator;
    Terrain::Chunk *m_chunk;
    std::vector<EntityID> m_chunkIDs;

    Terrain::ChunkMeshCreator m_meshCreator;
    int                       m_resolution;
};

} //namespace Spawner
} //namespace Cosmo

#endif //TERRAINSPAWNER_H
