#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponents.h"

namespace kda {
	class Pew : public Actor {
	public:
		CLASS_DECLARATION(Pew)

		bool Initialize() override;
		void Update(float dt) override;
		void onCollisionEnter(Actor* actor) override;


	private:
		float speed = 0;

		kda::PhysicsComponent* m_physicsComponent = nullptr;
	};
}