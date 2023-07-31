#pragma once
#include "Framework/Actor.h"

class Enemy : public kda::Actor
{
public:
	Enemy(float speed, float turnRate, const kda::Transform& transform, std::shared_ptr<kda::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireRate = 10.0f;
		m_fireTimer = m_fireRate;
	}
	void Update(float dt) override;
	void OnCollision(Actor* actor) override;
private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;
	int hp = 10;
};