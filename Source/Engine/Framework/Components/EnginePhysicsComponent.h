#pragma once
#include "PhysicsComponents.h"

namespace kda {
	class EnginePhysicsComponent : public PhysicsComponent {
		public:
			CLASS_DECLARATION(EnginePhysicsComponent)

			void Update(float dt) override;
			void ApplyForce(const vec2& force) override;
	};
}