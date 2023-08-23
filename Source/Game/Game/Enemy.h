#pragma once
#include "./Framework/Actor.h"
#include "Framework/Components/PhysicsComponents.h"

namespace kda {
	class Enemy : public Actor {
	public:
		CLASS_DECLARATION(Enemy)

		bool Initialize() override;


		void Update(float dt) override;
		void onCollision(Actor* actor) override;

		/*Enemy(float speed, float turnRate, const kda::Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{
			m_fireTime = 2.0f;
			m_fireRate = m_fireTime;
		}*/

	private:
		float speed = 0;
		float turnRate = 0;

		float fireTime = 3.0f;
		float fireRate = 0;
		int hp = 10;

		kda::PhysicsComponent* m_physicsComponent = nullptr;
	};
}