#pragma once
#include "Framework/Actor.h"

namespace kda {
	class Pew : public Actor {
	public:
		CLASS_DECLARATION(Pew)

		bool Initialize() override;
		void Update(float dt) override;
		void onCollision(Actor* actor);
		//void Read(const json_t& value);

		/*
		Pew(float speed, const kda::Transform& transform) :
			Actor{ transform },
			m_speed{ speed }
		{
			lifespan = 2.0f;
		}
		*/


	private:
		float speed = 0;
		float turnRate = 0;
	};
}