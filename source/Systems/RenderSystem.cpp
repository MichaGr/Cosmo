#include "RenderSystem.h"
#include "../utils.h"
#include <iostream>
#include "SFML/Graphics/CircleShape.hpp"

#include "../Components/PositionComponent.h"
#include "../Components/ColorComponent.h"

#include "../Memory/PoolManager.h"
#include "../Constants.h"

#include "../config.h"
#include "../../glm-0.9.9.3/glm/gtc/quaternion.hpp"

#include "../Math/Noise/SimplexNoise.h"
#include "VoxelProc.h"
#include "Math/SurfaceGeneration/Voxels/include/Voxels.h"
#include "Math/SurfaceGeneration/Voxels/include/Version.h"
#include "../TestMaterialMap.h"
#include "../World.h"

template<typename T>
constexpr auto
BUFFER_OFFSET(T offset)
{ return (reinterpret_cast<void *>(offset)); }

std::vector<glm::vec3>
CalcNormals(std::vector<unsigned int> &pIndices,
            std::vector<glm::vec3> &pVertices)
{
    std::vector<glm::vec3> ret;
    ret.resize(pVertices.size());

    for(unsigned int i = 0; i < ret.size();++i)
    {
        ret[i] = glm::vec3(0,0,0);
    }
    for (unsigned int i = 0; i < pIndices.size(); i += 3)
    {
        unsigned int Index0 = pIndices[i];
        unsigned int Index1 = pIndices[i + 1];
        unsigned int Index2 = pIndices[i + 2];
        glm::vec3    v1     = pVertices[Index1] - pVertices[Index0];
        glm::vec3    v2     = pVertices[Index2] - pVertices[Index0];
        glm::vec3    Normal = glm::cross(v1, v2);
        Normal = glm::normalize(Normal);

        ret[Index0] += Normal;
        ret[Index1] += Normal;
        ret[Index2] += Normal;
    }

    for (unsigned int i = 0; i < pVertices.size(); i++)
    {
        ret[i] = glm::normalize(ret[i]);
    }

    return ret;
}


namespace Cosmo
{

namespace Systems
{

//-----------------------------------------------------------------------------

RenderSystem::RenderSystem(sf::RenderWindow *window)
        : m_window(window)
{
    m_name = "RenderSystem";

}

//-----------------------------------------------------------------------------

RenderSystem::~RenderSystem()
{
    m_window = nullptr;
}

//-----------------------------------------------------------------------------

void
RenderSystem::init(World *manager)
{
    std::cout << "init render" << std::endl;
    m_world           = manager;
    m_componentBitset = m_world->initComponentBitset<Components::Mesh>();

    m_mv = m_world->getView()
                  ->projection * m_world->getCamera()
                                        ->view;
    dirLight.name             = "dirLight";
    dirLight.direction        = glm::vec3(-1.0f, -1.0f, -0.5f);
    dirLight.direction        = glm::normalize(dirLight.direction);
    dirLight.color            = glm::vec3(1.0f, 1.0f, 1.0f);
    dirLight.ambientIntensity = 0.2f;
    dirLight.diffuseIntensity = 0.8f;

    pointLight.name             = "pointLight";
    pointLight.position         = glm::vec3(5.0, 0.0f, 5.0f);
    pointLight.color            = glm::vec3(1.0f, 1.0f, 1.0f);
    pointLight.ambientIntensity = 0.1f;
    pointLight.diffuseIntensity = 0.3f;
    pointLight.attenuation
              .constant         = 0.0f;
    pointLight.attenuation
              .linear           = 0.0f;
    pointLight.attenuation
              .exp              = 0.5f;


    //test mesh

    EntityID         testID = m_world->getManager()
                                     ->createNewEntity();
    Components::Mesh &m     = m_world->getManager()
                                     ->addComponent<Components::Mesh>(testID);
    m.loadMesh("tree.obj");

    m_world->getManager()
           ->addComponent<Components::Position>(testID)
           .set(0.0f, 0.0f, 0.0f, 1.0f);

    m_world->getManager()
           ->finalizeEntity(testID);


    //marching cubes

    EntityID id = m_world->getManager()
                         ->createNewEntity();
    m_world->getManager()
           ->addComponent<Components::Mesh>(id);

    initScreenSpaceQuad();

    m_screenSize = glm::vec3({float(m_window->getSize()
                                            .x), float(m_window->getSize()
                                                               .y), 0.0f});

    m_geometryPassProgram.addShaders("geometryPass", GL_VERTEX_SHADER, GL_FRAGMENT_SHADER);
    m_geometryPassProgram.create();
    m_lightingPassProgram.addShaders("lightingPass", GL_VERTEX_SHADER, GL_FRAGMENT_SHADER);
    m_lightingPassProgram.create();


    m_mv = m_world->getView()
                  ->projection * m_world->getCamera()
                                        ->view;

    GLint texLoc;


    m_gBuffer.Init(m_window->getSize()
                           .x, m_window->getSize()
                                       .y);


    m_geometryPassProgram.use();


    m_geometryPassProgram.addUniform("mv_matrix", &m_mv);

    m_lightingPassProgram.use();

    m_lightingPassProgram.addUniform("gDirectionalLight", &dirLight);
    m_lightingPassProgram.addUniform("gEyeWorldPos", &m_cameraPositionLightingPass);

    m_lightingPassProgram.addUniform("gScreenSize", &m_screenSize);

    c          = 0.0001f;
    m_fogColor = glm::vec3(144.0f / 255.0f, 202.0f / 255.0f, 249.0f / 255.0f);
    m_lightingPassProgram.addUniform("b", &b);
    m_lightingPassProgram.addUniform("c", &c);
    m_lightingPassProgram.addUniform("fogColor", &m_fogColor);

    texLoc = glGetUniformLocation(m_lightingPassProgram.getID(), "gPositionMap");
    glUniform1i(texLoc, 0);
    texLoc = glGetUniformLocation(m_lightingPassProgram.getID(), "gColorMap");
    glUniform1i(texLoc, 1);
    texLoc = glGetUniformLocation(m_lightingPassProgram.getID(), "gNormalMap");
    glUniform1i(texLoc, 2);

}

//-----------------------------------------------------------------------------

void
RenderSystem::initScreenSpaceQuad()
{
    glGenVertexArrays(1, &m_vaoScreenSpaceQuad);
    glBindVertexArray(m_vaoScreenSpaceQuad);
    glGenBuffers(1, &m_vboScreenSpaceQuad);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboScreenSpaceQuad);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), screenspacequad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
}

//-----------------------------------------------------------------------------

void
RenderSystem::onUpdate()
{
    //    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glClearColor(m_fogColor.x, m_fogColor.y, m_fogColor.z, 1.0f);

    this->geometryPass();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    this->beginLightingPass();
    this->lightingPass();

    glUseProgram(0);
    m_window->display();
}

//-----------------------------------------------------------------------------

void
RenderSystem::drawMeshes()
{
    EntitySet *set = m_world->getEntitySet(m_componentBitset);

    for (EntityID id : *set)
    {
        Components::Mesh &mesh = m_world->getManager()
                                        ->getComponent<Components::Mesh>(id);
        mesh.render();
    }
}

//-----------------------------------------------------------------------------

void
RenderSystem::geometryPass()
{
    m_geometryPassProgram.use();

    m_gBuffer.BindForWriting();

    glDepthMask(GL_TRUE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);


    m_mv           = m_world->getView()
                            ->projection * m_world->getCamera()
                                                  ->view;
    m_normalMatrix = glm::transpose(glm::inverse(glm::mat3(m_world->getCamera()
                                                                  ->view)));

    m_geometryPassProgram.updateUniforms();

    this->drawMeshes();

    //TODO: support instanced mesh drawing
    //this->drawMeshInstances();

    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);

}

//-----------------------------------------------------------------------------

void
RenderSystem::beginLightingPass()
{
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

    m_gBuffer.BindForReading(0);
    glClear(GL_COLOR_BUFFER_BIT);
}

//-----------------------------------------------------------------------------

void
RenderSystem::lightingPass()
{
    m_lightingPassProgram.use();

    //update uniforms
    m_cameraPositionLightingPass = m_world->getCamera()
                                          ->position;

    m_lightingPassProgram.updateUniforms();

    //draw screen space quad
    glBindVertexArray(m_vaoScreenSpaceQuad);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

//-----------------------------------------------------------------------------

} //namespace Systems
} //namespace Cosmo
