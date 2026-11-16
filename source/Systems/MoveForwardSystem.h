#ifndef Cosmo_MOVEFORWARDSYSTEM_H
#define Cosmo_MOVEFORWARDSYSTEM_H

#include "System.h"

namespace Cosmo
{

	namespace Systems
	{

		class MoveForwardSystem : public System
		{
		public:
			MoveForwardSystem() { m_name = "MoveForwardSystem"; }
            void init(World* world) override;
            void onUpdate() override;
			~MoveForwardSystem() override;
		};

	} //namespace Systems

} //namespace Cosmo

#endif //Cosmo_MOVEFORWARDSYSTEM_H
