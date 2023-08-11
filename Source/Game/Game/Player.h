#pragma once
#include "./Framework/Actor.h"
#include "Framework/Components/PhysicsComponents.h"

class Player : public kda::Actor {
	public:
		Player(float speed, float turnRate, const kda::Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{}

		bool Initialize() override;

		void Update(float dt) override;
		void onCollision(Actor* actor) override;

	private:
		float m_speed = 0;
		float m_turnRate = 0;
		int hp = 100;

		kda::PhysicsComponent* m_physicsComponent = nullptr;
};