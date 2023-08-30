#pragma once
#include "Component.h"
#include <Core/Math/Vector2.h>

namespace kda {
	class PhysicsComponent : public Component{
		public:
			//void Update(float dt) override;
			virtual void ApplyForce(const vec2& force) = 0;
			virtual void ApplyTorque(float torque) = 0;

			virtual void SetVelocity(const vec2& velocity) { this->velocity = velocity; }
			virtual void SetGravityScale(float scale) {}

		public:
			vec2 velocity;
			vec2 acceleration;
			float mass = 1.0f;
			float damping = 0.0f;
	};
}