#ifndef ENTITYCOMPONENTSYTEM_RENDERSYSTEM_H
#define ENTITYCOMPONENTSYTEM_RENDERSYSTEM_H

#include "System.h"

#include "GL/glew.h"
#include "Rendering/Program.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include "../Components/PositionComponent.h"
#include "../glm-0.9.9.3/glm/gtc/matrix_transform.hpp"
#include "../Rendering/GBuffer.h"
#include "../Rendering/Lighting/DirectionalLight.h"
#include "../Rendering/Lighting/PointLight.h"
#include "Components/MeshComponent.h"
#include "../Math/SurfaceGeneration/DualMarchingCubes/dualmc.h"

namespace Cosmo
{

namespace Systems
{

const static float screenspacequad[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f
};

class RenderSystem
        : public System
{
public: //methods

    explicit RenderSystem(sf::RenderWindow *window);

    void init(World *world) override;

    ~RenderSystem() override;

protected: //methods

    void onUpdate() override;

private: //methods

    void initScreenSpaceQuad();

    void drawMeshes();

    //void draw2D();
    void geometryPass();

    void beginLightingPass();

    void lightingPass();

private: //variables

    Program program;

    DirectionalLight dirLight;
    PointLight       pointLight;

    /// struct for volume data information
    struct Volume
    {
        // volume grid extents
        int32_t            dimX;
        int32_t            dimY;
        int32_t            dimZ;
        // bit depth, should be 8 or 16
        int32_t            bitDepth;
        /// volume data
        std::vector<float> data;
    };

    /// example volume
    Volume volume;

    std::vector<dualmc::Vertex> dualmcVertices;
    std::vector<dualmc::Quad>   dualmcQuad;

    std::vector<glm::vec3>    dVertices;
    std::vector<unsigned int> dIndices;
    std::vector<glm::vec3>    dColors;
    std::vector<glm::vec3>    dNormals;
    float                     b;
    float                     c;
    glm::vec3                 m_fogColor;

    sf::RenderWindow *m_window;

    GLuint m_vboScreenSpaceQuad;
    GLuint m_vaoScreenSpaceQuad;

    Program m_geometryPassProgram;
    Program m_lightingPassProgram;

    GBuffer m_gBuffer;

    glm::mat4        m_mv;
    glm::mat3        m_normalMatrix;
    glm::mat4        m_mvLightingPass;
    glm::vec3        m_cameraPositionLightingPass;
    DirectionalLight m_directionalLight;
    float            m_matSpecularIntensity;
    float            m_specularPower;
    glm::vec3        m_screenSize;

    GLuint cameraID;
    GLuint camPosID;
    GLuint m_normalID;
};

} //namespace Systems

} //namespace Cosmo

#endif //ENTITYCOMPONENTSYTEM_RENDERSYSTEM_H
