#pragma once
#include "./Framework/Actor.h"
#include "Framework/Components/PhysicsComponents.h"

namespace kda {

	class Player : public kda::Actor {
	public:
		CLASS_DECLARATION(Player)


		bool Initialize() override;

		void Update(float dt) override;
		void onCollisionEnter(Actor* actor) override;

		/*Player(float speed, float turnRate, const kda::Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{}*/
	private:
		float speed = 0;
		float turnRate = 0;
		int hp = 10;

		kda::PhysicsComponent* m_physicsComponent = nullptr;
	};
}