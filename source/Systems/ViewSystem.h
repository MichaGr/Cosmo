#ifndef VIEWSYSTEM_H
#define VIEWSYSTEM_H

#include "System.h"
#include "../Components/CameraComponent.h"
#include "../Components/ViewComponent.h"

namespace Cosmo
{
namespace Systems
{
class ViewSystem
        : public System
{
public: //methods
    void init(World *world) override;

    void onUpdate() override;

    ~ViewSystem() override;

private: //methods
    void normalize();

    void updateProjectionMatrix();

    void updateViewMatrix();

private: //variables
    Components::Camera *m_camera;
    Components::View   *m_view;
};


} //namespace Systems
} //namespace Cosmo

#endif //VIEWSYSTEM_H
