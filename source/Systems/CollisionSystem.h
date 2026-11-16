#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "System.h"
#include "../EventManager/EventHandler.h"

#include "../../glm-0.9.9.3/glm/gtc/matrix_transform.hpp"
namespace Cosmo
{
	namespace Systems
	{
		class CollisionSystem : public System, public EventHandler
		{
		public:
			CollisionSystem(EventQueue* queue)
				: EventHandler(queue)
			{
				m_name = "CollisionSystem";
			}

            void init(World* world) override;
            void onUpdate() override;

		private:
			struct OBB
			{
				glm::vec3 Pos, AxisX, AxisY, AxisZ, Half_size;
			};

			bool collideAABB(unsigned int id0, unsigned int id1);
			bool collideOBB(float deltaTime, unsigned int id0, unsigned int id1);

			bool getSeperatingPlane(const glm::vec3& RPos,
				const glm::vec3& plane,
				const OBB& box1,
				const OBB& box2);
		};

	}
}

#endif //COLLISIONSYSTEM_H
