#include "PewPew.h"

void PewPew::Update(float dt)
{
	Actor::Update(dt);
	kda::vec2 forward = kda::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kda::g_time.GetDeltaTime();
	m_transform.position.x = kda::Wrap(m_transform.position.x, (float)kda::g_renderer.getWidth());
	m_transform.position.y = kda::Wrap(m_transform.position.y, (float)kda::g_renderer.getHeight());
		
}

void PewPew::OnCollision(Actor* actor)
{
	if (m_tag != "Big") {
		m_lifespan = 0.0f;
	}
}
