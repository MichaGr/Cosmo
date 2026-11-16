#include "ViewSystem.h"
#include "../Memory/PoolManager.h"
#include "../glm-0.9.9.3/glm/gtc/matrix_transform.hpp"
#include "../glm-0.9.9.3/glm/gtc/quaternion.hpp"

#define GLM_ENABLE_EXPERIMENTAL true

#include "../glm-0.9.9.3/glm/gtx/transform.hpp"

#include "../Components/PositionComponent.h"
#include "../Components/ForwardComponent.h"
#include "../World.h"

namespace Cosmo
{
namespace Systems
{

//-----------------------------------------------------------------------------

ViewSystem::~ViewSystem()
{
    m_name = "ViewSystem";
}

//-----------------------------------------------------------------------------

void
ViewSystem::init(World *world)
{
    std::cout << "init view" << std::endl;
    m_world  = world;
    m_camera = m_world->getCamera();
    m_view   = m_world->getView();

    m_camera->position  = glm::vec3(1.0f, 10.0f, -3.0f);
    m_camera->direction = glm::vec3(1.0f, 0.0f, 0.0f);
    m_camera->up        = glm::vec3(0.0f, 1.0f, 0.0f);

    m_camera->horizontalAngle = 0.0f;
    m_camera->verticalAngle   = 0.0f;
    m_camera->maxSpeed        = 0.25f;
    m_camera->zoom            = 1.0f;
    m_camera->speed           = glm::vec3(1.0f, 1.0f, 1.0f);

    m_view->nearPlane = 0.01f;
    m_view->farPlane  = 1000.0f;
    m_view->width     = 1440.0f;
    m_view->height    = 900.0f;
    m_view->fov       = 45.0f;

    float hor, vert;
    hor  = m_camera->horizontalAngle;
    vert = m_camera->verticalAngle;

    m_camera->right = glm::cross(m_camera->direction, m_camera->up);

    updateProjectionMatrix();
    updateViewMatrix();
    std::cout << "end init view" << std::endl;
}

//-----------------------------------------------------------------------------

void
ViewSystem::onUpdate()
{
    this->normalize();

    updateProjectionMatrix();
    updateViewMatrix();
}

//-----------------------------------------------------------------------------

void
ViewSystem::normalize()
{
    if (m_camera->verticalAngle > 89.0f)
    {
        m_camera->verticalAngle = 89.0f;
    }

    if (m_camera->verticalAngle < -89.0f)
    {
        m_camera->verticalAngle = -89.0f;
    }

    if (m_camera->horizontalAngle > 360.0f)
    {
        m_camera->horizontalAngle -= 360.0f;
    }

    if (m_camera->horizontalAngle < -360.0f)
    {
        m_camera->horizontalAngle += 360.0f;
    }
}

//-----------------------------------------------------------------------------

void
ViewSystem::updateViewMatrix()
{
    float horizontalAngle = glm::radians(m_camera->horizontalAngle);
    float verticalAngle   = glm::radians(m_camera->verticalAngle);

    m_camera->direction
            .x = cosf(verticalAngle) * sinf(horizontalAngle);
    m_camera->direction
            .y = sinf(verticalAngle);
    m_camera->direction
            .z = cosf(verticalAngle) * cosf(horizontalAngle);

    m_camera->view = glm::lookAt(m_camera->position,
                                 m_camera->position + m_camera->direction,
                                 m_camera->up);
}

//-----------------------------------------------------------------------------

void
ViewSystem::updateProjectionMatrix()
{
    m_view->projection =
            glm::perspective(glm::radians(m_view->fov),
                             m_view->aspectRatio(),
                             m_view->nearPlane,
                             m_view->farPlane);
}

//-----------------------------------------------------------------------------
} //namespace Systems
} //namespace Cosmo
