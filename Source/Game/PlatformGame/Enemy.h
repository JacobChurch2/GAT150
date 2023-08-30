#pragma once
#include "./Framework/Actor.h"
#include "Framework/Components/PhysicsComponents.h"

namespace kda {

	class Enemy : public kda::Actor {
	public:
		CLASS_DECLARATION(Enemy)


		bool Initialize() override;

		void Update(float dt) override;
		void onCollisionEnter(Actor* actor) override;
		void onCollisionExit(Actor* actor) override;

	private:
		float speed = 0;
		float turnRate = 0;
		int hp = 100;

		kda::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
