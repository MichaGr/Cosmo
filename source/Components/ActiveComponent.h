#ifndef Cosmo_ACTIVECOMPONENT_H
#define Cosmo_ACTIVECOMPONENT_H

#include "Component.h"

namespace Cosmo
{

namespace Components
{

class Active : public Component
{
public:
    void init() override;
    ~Active() override;

    bool isActive() const;
private:
    bool m_active;
};

} //namespace Components

} //Cosmo

#endif //Cosmo_ACTIVECOMPONENT_H
