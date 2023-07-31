#pragma once
#include "Framework/Actor.h"

class PewPew : public kda::Actor
{
public:
	PewPew(float speed, const kda::Transform& transform, std::shared_ptr<kda::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		m_lifespan = -1.0f;
	}
	~PewPew() = default;

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;
private:
	float m_speed = 0;
	float m_turnRate = 0;
};