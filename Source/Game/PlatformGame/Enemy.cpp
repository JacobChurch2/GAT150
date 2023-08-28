#include "Enemy.h"
#include "Framework/Framework.h"
#include "Render/Renderer.h"
#include "Input/InputSystem.h"


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
		float dir = 0;

		kda::vec2 forward = kda::vec2{ 1,0 };
		m_physicsComponent->ApplyForce(forward * speed * dir);

		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kda::g_time.setTimeScale(0.5f);
		else kda::g_time.setTimeScale(1.0f);
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
		READ_DATA(value, hp);

	}
}