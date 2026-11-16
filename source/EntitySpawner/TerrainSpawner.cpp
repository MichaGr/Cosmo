#include "TerrainSpawner.h"
#include <iostream>
#include <math.h>

#include "../Components/PositionComponent.h"
#include "../Components/ColorComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/ScaleComponent.h"
#include "../Math/Noise/SimplexNoise.h"
#include "../Constants.h"
#include <omp.h>
#include "../utils.h"
namespace Cosmo
{

	namespace Spawner
	{
		void TerrainSpawner::init(World* world)
		{
			m_world = world;
			std::cout << "after noise generation" << std::endl;
			generator = MathLib::PerlinNoise(4);
			m_resolution = 1;
		}

		void TerrainSpawner::setParameters(Terrain::Chunk* chunk, int resolution)
		{
			m_chunk = chunk;
			m_resolution = resolution;
		}

		double TerrainSpawner::remap(double chunkID, double blockID, double c, double b_cp)
		{
			return (chunkID + blockID / c) / b_cp + 0.5;
		}

		double TerrainSpawner::value(double chunkPositionX, double chunkPositionZ, double x, double z)
		{
            double c = (double)Cosmo::chunkSize;
			double b = border;
			double b_c = b / c;
			double b_cp = 2.0 * b_c;
			double pi = 3.141592653;
			double rate = 4096;

			double s = remap((double)chunkPositionX, floor((double)x), c, b_cp);
			double t = remap((double)chunkPositionZ, floor((double)z), c, b_cp);
			//double s = x / (double)m_size;
			//double t = y / (double)m_size;
			double dx = rate;
			double dz = rate;

			double nx = cos(s * 2.0 * pi)*dx / (2.0 * pi);
			double ny = cos(t * 2.0 * pi)*dz / (2.0 * pi);
			double nz = sin(s * 2.0 * pi)*dx / (2.0 * pi);
			double nw = sin(t * 2.0 * pi)*dz / (2.0 * pi);

			double res = MathLib::SimplexNoise::octaveNoise(nx, ny, nz, nw, 6, 0.2, 4096);

			res = floor((res * 2.0 - 1.0)*64.0);
			if (res < 0)
			{
				res = floor(lerp<double>(res, 0, 0.95));
			}

			return res;
		}

		void TerrainSpawner::spawn()
		{

//            bool useVoxels = false;
//
//            //TODO: move this whole part to terrainspawnersystem
//            //TODO: also renmae terrainspawnersystem, terrainmanagersystem?
//            //Voxels
//            if (useVoxels)
//            {
//                std::cout << "Voxel kram " << std::endl;
//                //init
//                if (InitializeVoxels(VOXELS_VERSION, nullptr, nullptr) != Voxels::InitError::IE_Ok)
//                {
//                    std::cout << "init Voxels failed" << std::endl;
//                }
//
//
//                //creation
//                Voxels::ProceduralParams params;
//                params.DimensionFactor = 0.25f;
//                params.ScaleFactor     = 7.5f;
//
//                std::cout << "Starting surface calculation" << std::endl;
//
//                Voxels::VoxelProc *m_Surface = new Voxels::VoxelProc(glm::vec3(0.0f, 0.0f, 1.0f), 5.0f, params);
//                //    m_Surface.reset(new Voxels::VoxelProc(XMFLOAT3(0.0f, 0.0f, 1.0f),
//                //        5.0f,
//                //        params));
//
//                std::cout << "Starting grid" << std::endl;
//
//                Voxels::Grid *grid = Voxels::Grid::Create(64, 64, 64, 0, 0, 0, 1, m_Surface);
//
//                delete m_Surface;
//
//                auto polygonizer                = new Voxels::Polygonizer;
//
//                std::cout << "starting polygonization" << std::endl;
//
//                //TODO add materialmap
//                //MaterialTable* materialMap = new MaterialTable;
//                //materialMap->Load("/home/ood/Downloads/volumerendering-master/media/materials.json");
//
//                TestMaterialTable      *materialMap;
//                Voxels::PolygonSurface *surface = polygonizer->Execute(*grid, materialMap);
//
//                std::cout << "finished polygonization" << std::endl;
//                delete materialMap;
//                const Voxels::BlockPolygons *polygons = surface->GetBlockForLevel(0, 0);
//
//                std::cout << "finished" << std::endl;
//                unsigned int                *countV = nullptr;
//                unsigned int                *countI = nullptr;
//                const Voxels::PolygonVertex *verts  = polygons->GetVertices(countV);
//                const unsigned int          *inds   = polygons->GetIndices(countI);
//
//                std::vector<Components::Mesh::Vertex> vertsVec;
//                std::vector<unsigned int>             indsVec;
//
//                for (unsigned int i = 0; i < *countV; ++i)
//                {
//                    Components::Mesh::Vertex v;
//                    v.position = glm::vec3(verts[i].Position
//                                                   .x,
//                                           verts[i].Position
//                                                   .y,
//                                           verts[i].Position
//                                                   .z);
//                    v.normal   = glm::vec3(verts[i].Normal
//                                                   .x,
//                                           verts[i].Normal
//                                                   .y,
//                                           verts[i].Normal
//                                                   .z);
//                    v.color    = glm::vec3(0.0f, 1.0f, 0.0f);
//                    vertsVec.push_back(v);
//                }
//
//                for (unsigned int i = 0; i < *countI; ++i)
//                {
//                    indsVec.push_back(inds[i]);
//                }
//
//                Components::Mesh::MeshEntry tmpMeshEntry;
//                tmpMeshEntry.init(vertsVec, indsVec);
//
//                m_world->getManager()
//                       ->getComponent<Components::Mesh>(id)
//                       .m_entries
//                       .push_back(tmpMeshEntry);
//
//                m_world->getManager()
//                       ->finalizeEntity(id);
//
//            }
//            else
//            {
//                //Dual Marching Cubes
//
//                unsigned int      q = 0;
//                for (unsigned int i = 0; i < 4; ++i)
//                {
//                    for (unsigned int j = 0; j < 4; ++j, ++q)
//                    {
//                        //            std::cout << "i,j: " << i << " " << j << std::endl;
//                        Components::Mesh::MeshEntry tmpMeshEntry;
//                        volume.data
//                              .clear();
//                        dualmcVertices.clear();
//                        dualmcQuad.clear();
//                        dNormals.clear();
//                        dVertices.clear();
//                        dIndices.clear();
//                        dColors.clear();
//                        glm::ivec3 dim(32, 32, 32);
//                        volume.dimX = dim.x;
//                        volume.dimY = dim.y;
//                        volume.dimZ = dim.z;
//
//                        volume.data
//                              .resize((dim.x + 3) * dim.y * (dim.z + 3));
//                        //            std::cout << "before volume" << std::endl;
//                        unsigned int      p = 0;
//                        for (unsigned int x = i * volume.dimX; x <= (i + 1) * (volume.dimX) + 2; ++x)
//                        {
//                            for (unsigned int y = 0; y < volume.dimY; ++y)
//                            {
//                                for (unsigned int z = j * volume.dimZ; z <= (j + 1) * (volume.dimZ) + 2; ++z, ++p)
//                                {
//                                    float value;
//
//                                    value = MathLib::SimplexNoise::octaveNoise(1.0f / float(128) * float(x),
//                                                                               1.0f / float(128) * float(y),
//                                                                               1.0f / float(128) * float(z), 1, 4, 0.5, 0.3);
//                                    value = value - 0.03f * float(y);
//                                    value = y < 1 ? 1.0f : value;
//                                    volume.data
//                                          .at(p) = value;
//                                }
//                            }
//                        }
//                        //            std::cout << "after volume" << std::endl;
//                        dualmc::DualMC<float> builder;
//
//                        builder.build(&volume.data
//                                             .front(),
//                                      volume.dimX + 3,
//                                      volume.dimY,
//                                      volume.dimZ + 3,
//                                      -0.1f,
//                                      true,
//                                      true,
//                                      dualmcVertices,
//                                      dualmcQuad);
//
//
//                        p = 0;
//                        float minX,maxX,minY,maxY,minZ,maxZ = 0.0f;
//
//                        minX = maxX = dualmcVertices.at(0).x;
//                        minY = maxY = dualmcVertices.at(0).y;
//                        minZ = maxZ = dualmcVertices.at(0).z;
//                        for (dualmc::Vertex &v : dualmcVertices)
//                        {
//                            minX = minX < v.x ? minX : v.x;
//                            minY = minY < v.y ? minY : v.y;
//                            minZ = minZ < v.z ? minZ : v.z;
//
//                            maxX = maxX > v.x ? maxX: v.x;
//                            maxY = maxY > v.y ? maxY: v.y;
//                            maxZ = maxZ > v.z ? maxZ: v.z;
//                            glm::vec3 v2(float(v.x) + float(j * volume.dimX), float(v.y), float(v.z) + float(i * volume.dimZ));
//                            glm::vec3 c(67.0f / 255.0f, 160.0f / 255.0f, 71.0f / 255.0f);
//                            glm::vec3 baseColor(255.0f / 255.0f, 236.0f / 255.0f, 179.0f / 255.0f);
//                            c = glm::mix(baseColor, c, glm::clamp(float(v.y) / 15.0f, 0.0f, 1.0f));
//                            dVertices.push_back(v2);
//                            dColors.push_back(c);
//                        }
//
//                        std::cout << "min: " << minX << "," <<minY << "," << minZ << std::endl;
//                        std::cout << "max: " << maxX << "," <<maxY << "," << maxZ << std::endl;
//                        //splint into triangles
//                        for (dualmc::Quad &q : dualmcQuad)
//                        {
//                            dIndices.push_back(q.i0);
//                            dIndices.push_back(q.i1);
//                            dIndices.push_back(q.i2);
//                            dIndices.push_back(q.i0);
//                            dIndices.push_back(q.i2);
//                            dIndices.push_back(q.i3);
//                        }
//
//                        dNormals = CalcNormals(dIndices, dVertices);
//
//                        Components::Mesh::Vertex              tmpV;
//                        std::vector<Components::Mesh::Vertex> verts;
//
//                        for (unsigned int k = 0; k < dVertices.size(); ++k)
//                        {
//                            tmpV.normal   = dNormals.at(k);
//                            tmpV.position = dVertices.at(k);
//                            tmpV.color    = dColors.at(k);
//                            verts.push_back(tmpV);
//                        }
//
//                        tmpMeshEntry.init(verts, dIndices);
//
//                        m_world->getManager()
//                               ->getComponent<Components::Mesh>(id)
//                               .m_entries
//                               .push_back(tmpMeshEntry);
//                    }
//                }
//
//                m_world->getManager()
//                       ->finalizeEntity(id);
//            }


#pragma omp parallel for
            for (int x = 0; x < Cosmo::chunkSize; x += m_resolution)
			{
				//for (double y = 0.0; y < m_size; y+= 1.0)
                for (int y = 0; y < Cosmo::chunkSize; y+= m_resolution)
				{

					double res = this->value((double)m_chunk->getPosition().x, (double)m_chunk->getPosition().z, floor((double)x), floor((double)y));

					EntityID id;
#pragma omp critical 
					{
						id = m_world->getManager()->createNewEntity();
						m_chunk->addBlockId(id);
						m_meshCreator.addBlock(x, (int)res, y);
					}

                    m_world->getManager()->addComponent<Components::Position>(id).set(x + m_chunk->getPosition().x * Cosmo::chunkSize,
						res,
                        y + m_chunk->getPosition().z * Cosmo::chunkSize);
 
					m_world->getManager()->addComponent<Components::Collider>(id);
					m_world->getManager()->getComponent<Components::Collider>(id).aabb.pos = glm::vec3({ x,res,y });
					m_world->getManager()->getComponent<Components::Collider>(id).aabb.size = glm::vec3({ m_resolution,m_resolution,m_resolution });

					m_world->getManager()->addComponent<Components::Scale>(id).set(m_resolution, m_resolution, m_resolution);

					m_world->getManager()->addComponent<Components::Color>(id);
					if (res > 0)
					{
						//vec4(0.6,0.7,0.5,1)
						glm::vec3 c = lerp<glm::vec3>(glm::vec3({ 0.2f, 0.8f, 0.4f }), glm::vec3({ 0.4f,0.8f,0.1f }), float(res) / 16.0f);
						m_world->getManager()->getComponent<Components::Color>(id).set(c.x, c.y, c.z);
					}
					else
					{
						//vec4(0.2, 0.8, 0.4, 1)
						glm::vec3 c = lerp <glm::vec3>(glm::vec3({ 0.2f, 0.8f, 0.4f }), glm::vec3({ 0.0f,0.4f,0.2f }), float(res) / -8.0f);
						m_world->getManager()->getComponent<Components::Color>(id).set(c.x, c.y, c.z);
					}

					m_world->getManager()->finalizeEntity(id);
				}
			}
		}
	}
}
