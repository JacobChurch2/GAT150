#include "Player.h"
#include "Framework/Framework.h"
#include "Render/Renderer.h"
#include "Input/InputSystem.h"


namespace kda {
	CLASS_DEFINITION(Player)

	bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kda::PhysicsComponent>();

		return true;
	}

	void Player::Update(float dt) {
		Actor::Update(dt);

		//movement
		float dir = 0;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_LEFT) || kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_RIGHT) || kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;
		
		kda::vec2 forward = kda::vec2{ 1,0 };
		m_physicsComponent->ApplyForce(forward * speed * dir);

		//jump
		bool onGround = (groundCount > 0);
		if (onGround && kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kda::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) 
		{
			kda::vec2 up = kda::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(up * jump);
		}

		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kda::g_time.setTimeScale(0.5f);
		else kda::g_time.setTimeScale(1.0f);
	}

	void Player::onCollisionEnter(Actor* actor) {
		if (actor->tag == "Enemy") {
			hp -= 5;
		}
		if (hp <= 0) {
			destroyed = true;
			kda::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		}
		if (actor->tag == "Ground") groundCount++;
	}

	void Player::onCollisionExit(Actor* actor) 
	{
		if (actor->tag == "Ground") groundCount--;
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, jump);
		READ_DATA(value, hp);

	}
}