#ifndef Cosmo_UPDATEBOUNDINGBOXESSYSTEM_H
#define Cosmo_UPDATEBOUNDINGBOXESSYSTEM_H

#include "System.h"

namespace Cosmo
{

	namespace Systems
	{

		class UpdateBoundingBoxesSystem : public System
		{
		public:
			UpdateBoundingBoxesSystem() { m_name = "UpdateBoundingBoxesSystem"; }
            void init(World* world) override;
            void onUpdate() override;
			~UpdateBoundingBoxesSystem() override;
		};

	} //namespace Systems

} //namespace Cosmo

#endif //Cosmo_UPDATEBOUNDINGBOXESSYSTEM_H
