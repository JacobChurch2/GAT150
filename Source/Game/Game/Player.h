#pragma once
#include "Framework/Actor.h"

class Player : public kda::Actor
{
public:
	Player(float speed, float turnRate, const kda::Transform& transform, std::shared_ptr<kda::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}
	void Update(float dt) override;
	void OnCollision(Actor* actor) override;
	int getHP() { return hp; }
private:
	float m_speed = 0;
	float m_turnRate = 0;

	float bigBulletCooldown = 10;
	float bigBulletTimer = 0.0f;
	int hp = 100;
};