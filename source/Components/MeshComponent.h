#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "Component.h"
#include "../../glm-0.9.9.3/glm/vec2.hpp"
#include "../../glm-0.9.9.3/glm/vec3.hpp"
#include <vector>

#include "assimp/mesh.h"
#include "assimp/scene.h"
#include <GL/glew.h>
namespace Cosmo
{

	namespace Components
	{
        struct Mesh : public Component
		{
            Mesh();

            void render();

            bool loadMesh(const std::string& filepath);

            bool initFromScene(const aiScene* pScene, const std::string& filepath);
            void initMesh(unsigned int index, const aiMesh* paiMesh);
            bool initMaterials(const aiScene* pScene, const std::string& filepath);
            void clear();

#define INVALID_MATERIAL 0xFFFFFFFF

            struct Vertex
            {
                glm::vec3 position;
                glm::vec2 texCoords;
                glm::vec3 normal;
                glm::vec3 color;
            };

            struct MeshEntry
            {
                MeshEntry();
                ~MeshEntry();

                bool init(const std::vector<Vertex>& vertices,
                          const std::vector<unsigned int>& indices);

                GLuint VAO;
                GLuint VB;
                GLuint IB;
                unsigned int numIndices;
                unsigned int materialIndex;
            };


            std::vector<MeshEntry> m_entries;
            std::vector<GLuint> m_textures;
		};

	} //namespace Components

} //namespace EntityComponentSystem

#endif //MESHCOMPONENT_H
