#include "Enemy.h"
#include "Framework/Framework.h"
#include "Render/Renderer.h"
#include "Input/InputSystem.h"
#include "Player.h"


namespace kda {
	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kda::PhysicsComponent>();

		return true;
	}

	void Enemy::Update(float dt) {
		Actor::Update(dt);

		//movement
		kda::vec2 forward = kda::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();

		if (player) {
			kda::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}

		transform.position.x = kda::wrap(transform.position.x, (float)kda::g_renderer.GetWidth());
		transform.position.y = kda::wrap(transform.position.y, (float)kda::g_renderer.GetHeight());
	}

	void Enemy::onCollisionEnter(Actor* actor) {
		if (actor->tag == "Enemy") {
			hp -= 5;
		}
		if (hp <= 0) {
			destroyed = true;
			kda::EventManager::Instance().DispatchEvent("OnEnemyDead", 0);
		}
	}

	void Enemy::onCollisionExit(Actor* actor)
	{

	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
		READ_DATA(value, hp);

	}
}