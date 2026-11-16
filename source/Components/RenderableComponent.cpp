#include "RenderableComponent.h"

namespace Cosmo
{

namespace Components
{

bool Renderable::isVisible() const
{
    return m_visible;
}

Renderable::Renderable(const Renderable& renderable)
{
    m_visible = renderable.isVisible();
}

Renderable::~Renderable()
{}

void Renderable::init()
{
    m_visible = true;
}

} //namespace Components

} //namespace Cosmo
