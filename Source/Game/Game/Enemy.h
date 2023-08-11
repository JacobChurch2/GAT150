#pragma once
#include "./Framework/Actor.h"

class Enemy : public kda::Actor {
public:

	bool Initialize() override;

	Enemy(float speed, float turnRate, const kda::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireTime = 2.0f;
		m_fireRate = m_fireTime;
	}

	void Update(float dt) override;
	void onCollision(Actor* actor) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireTime = 3.0f;
	float m_fireRate = 0;
	int hp = 10;
};