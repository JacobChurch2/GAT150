#pragma once
#include "./Framework/Actor.h"

class Pew : public kda::Actor {
public:
	Pew(float speed, const kda::Transform& transform) :
		Actor{ transform },
		m_speed{ speed }
	{
		m_lifespan = 2.0f;
	}

	void Update(float dt) override;
	void onCollision(Actor* actor) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
};