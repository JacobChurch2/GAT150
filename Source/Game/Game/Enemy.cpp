#include "Enemy.h"
#include "Player.h"
#include "PewPew.h"
#include "Render/ModelManager.h"
#include "Framework/Game.h"
#include "Game/SpaceGame.h"
#include "Framework/Scene.h"
#include "Render/Render.h"
#include "Framework/Emitter.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	kda::vec2 forward = kda::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kda::vec2 direction = player->m_transform.position - m_transform.position;

		float turnAngle = kda::vec2::SignedAngle(forward, direction.Normalized());

		m_transform.rotation += turnAngle * dt;

		if (std::fabs(turnAngle) < kda::DegreesToRadians(30.0f))
		{
			//I see you!
			if (m_fireTimer <= 0)
			{
				m_fireTimer = m_fireRate;

				float rad = GetRadius() + 20;
				kda::vec2 temp {0.0f, -rad};
				temp = temp.Rotate(m_transform.rotation);

				//create pew pew
				kda::Transform transform{temp + m_transform.position, m_transform.rotation, 1 };
				std::unique_ptr<PewPew> pewPew = std::make_unique<PewPew>(400.0f, transform, kda::g_manager.get("EnemyBullet.txt"));
				pewPew->m_tag = "Enemy";
				m_scene->Add(std::move(pewPew));

				m_game->AddPoints(10);
			}
		}
	}

	m_transform.position += forward * m_speed * kda::g_time.GetDeltaTime();
	m_transform.position.x = kda::Wrap(m_transform.position.x, (float)kda::g_renderer.getWidth());
	m_transform.position.y = kda::Wrap(m_transform.position.y, (float)kda::g_renderer.getHeight());

	m_fireTimer -= dt;
}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->m_tag != "Enemy")
	{
		hp -= 5;
	}
	if (hp <= 0) 
	{
		m_game->AddPoints(100);
		m_destroyed = true;

		//create explosion
		kda::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 0;
		data.angle = 0;
		data.angleRange = kda::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = kda::Color{ 1, 0, 0, 1 };
		kda::Transform transform{ { m_transform.position }, 0, 1 };

		auto emitter = std::make_unique<kda::Emitter>(transform, data);
		emitter->m_lifespan = 0.1f;
		m_scene->Add(std::move(emitter));

		kda::g_audioSystem.PlayOneShot("Explosion");
	}
}
