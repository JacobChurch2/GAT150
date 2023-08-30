#include "Player.h"

#include "Framework/Framework.h"
#include "Render/Renderer.h"
#include "Input/InputSystem.h"


namespace kda {
	CLASS_DEFINITION(Player)

	bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimComponent>();

		return true;
	}

	void Player::Update(float dt) {
		Actor::Update(dt);
		bool onGround = (groundCount > 0);
		vec2 velocity = m_physicsComponent->velocity;

		//movement
		float dir = 0;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_LEFT) || kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_RIGHT) || kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;
		
		if (dir) {
			kda::vec2 forward = kda::vec2{ 1,0 };
			velocity.x += speed * dir * ((onGround) ? 1 : 0.07f) * dt;
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_physicsComponent->SetVelocity(velocity);
			//m_physicsComponent->ApplyForce(forward * speed * dir * ((onGround) ? 1 : 0.05f));
		}

		//jump
		if (onGround && kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kda::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) 
		{
			kda::vec2 up = kda::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(velocity + (up * jump));
		}

		m_physicsComponent->SetGravityScale((velocity.y > 0) ? 3 : 2);

		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kda::g_time.setTimeScale(0.5f);
		else kda::g_time.setTimeScale(1.0f);

		//animation
		if (std::fabs(velocity.x) > 0.2f)
		{
			if (dir != 0) m_spriteAnimComponent->flipH = (dir < 0);
			m_spriteAnimComponent->SetSequence("run");
		}
		else 
		{
			m_spriteAnimComponent->SetSequence("idle");
		}
	}

	void Player::onCollisionEnter(Actor* actor) {
		if (actor->tag == "Enemy") {
			hp -= 5;
		}
		if (hp <= 0) {
			destroyed = true;
			kda::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		}
		if (actor->tag == "Ground") {
			groundCount++;
		}
	}

	void Player::onCollisionExit(Actor* actor) 
	{
		if (actor->tag == "Ground") 
		{ 
			groundCount--;
		}
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, maxSpeed);
		READ_DATA(value, jump);
		READ_DATA(value, hp);

	}
}