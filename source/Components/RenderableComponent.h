#ifndef Cosmo_RENDERABLECOMPONENT_H
#define Cosmo_RENDERABLECOMPONENT_H

#include "Component.h"

namespace Cosmo
{

namespace Components
{

class Renderable : public Component
{
public:
    Renderable(const Renderable& renderable);
    void init() override;
    ~Renderable() override;

    void setVisibility(bool visible) {m_visible = visible;}

    bool isVisible() const;

private:
    bool m_visible;

};

} //namespace Components

} //namespace Cosmo

#endif //Cosmo_RENDERABLECOMPONENT_H
