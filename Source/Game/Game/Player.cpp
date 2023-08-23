#include "Player.h"
#include "Framework/Framework.h"
#include "Render/Renderer.h"
#include "Pew.h"
#include "SpaceGame.h"
#include "Input/InputSystem.h"
#include "Framework/Components/ModelRenderComponent.h"

namespace kda {
	CLASS_DEFINITION(Player)

	bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kda::PhysicsComponent>();
		auto collisionComponent = GetComponent<kda::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<kda::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;
			}
		}

		return true;
	}

	void Player::Update(float dt) {
		Actor::Update(dt);

		//movement
		float rotate = 0;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_LEFT)) rotate = -1;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_RIGHT)) rotate = 1;
		//transform.rotation += rotate * m_turnRate * kda::g_time.getDeltaTime();
		m_physicsComponent->ApplyTorque(rotate * turnRate);

		float thrust = 0;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_UP))thrust = 1;
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_UP)) {
			kda::EmitterData data;
			data.burst = false;
			data.burstCount = 10;
			data.spawnRate = 500;
			data.angle = 0;
			data.angleRange = kda::pi;
			data.lifetimeMin = 0.25f;
			data.lifetimeMax = 0.5f;
			data.speedMin = 25;
			data.speedMax = 50;
			data.damping = 0.5f;
			data.color = kda::Color{ 0, 1, 0, 1 };
			kda::Transform transform{ { this->transform.position }, 0, 2 };
			auto emitter = std::make_unique<kda::Emitter>(transform, data);
			emitter->lifespan = 0;
			m_scene->Add(std::move(emitter));
		}


		kda::vec2 forward = kda::vec2{ 0, -1 }.Rotate(transform.rotation);

		m_physicsComponent->ApplyForce(forward * speed * thrust);

		//m_transform.position += forward * m_speed * thrust * kda::g_time.getDeltaTime();
		transform.position.x = kda::wrap(transform.position.x, (float)kda::g_renderer.GetWidth());
		transform.position.y = kda::wrap(transform.position.y, (float)kda::g_renderer.GetHeight());

		//fire weapon

		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kda::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			auto weapon = INSTANTIATE(Pew, "Rocket");
			weapon->transform = { transform.position, transform.rotation + kda::DegreesToRadians(10.0f), 1 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));
		}

		//TODO::Get my second weapon
		// 
		// 
		//	if (weaponSelect == 1) {
		//		kda::Transform transform1{transform.position, transform.rotation, 1};
		//		std::unique_ptr<Pew> pew = std::make_unique<Pew>(400.0f, transform1);
		//		pew->tag = "Player";

		//		std::unique_ptr<kda::SpriteComponent> component = std::make_unique<kda::SpriteComponent>();
		//		component->m_texture = GET_RESOURCE(kda::Texture, "PlayerBullet.png", kda::g_renderer);
		//		pew->AddComponent(std::move(component));

		//		auto collisionComponent = std::make_unique<kda::CircleCollisionComponent>();
		//		collisionComponent->m_radius = 30.0f;
		//		pew->AddComponent(std::move(collisionComponent));

		//		pew->Initialize();
		//		m_scene->Add(std::move(pew));
		//	}
		//}

		////Big Weapon
		//if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_V) && !kda::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_V)) {
		//	kda::Transform transform1{transform.position, transform.rotation, 10};
		//	std::unique_ptr<Pew> pew = std::make_unique<Pew>(400.0f, transform1);
		//	pew->tag = "Player";

		//	std::unique_ptr<kda::ModelRenderComponent> component = std::make_unique<kda::ModelRenderComponent>();
		//	component->m_model = GET_RESOURCE(kda::Model, "PlayerShip.txt");
		//	pew->AddComponent(std::move(component));

		//	auto collisionComponent = std::make_unique<kda::CircleCollisionComponent>();
		//	collisionComponent->m_radius = 30.0f;
		//	pew->AddComponent(std::move(collisionComponent));

		//	pew->Initialize();
		//	m_scene->Add(std::move(pew));
		//}

		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kda::g_time.setTimeScale(0.5f);
		else kda::g_time.setTimeScale(1.0f);

		//std::cout << m_transform.position.x << " " << m_transform.position.y << std::endl;
	}

	void Player::onCollision(Actor* actor) {
		if (actor->tag != "Player") {
			hp -= 5;
		}
		if (hp <= 0) {
			destroyed = true;
			kda::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
			m_game->SetLives(m_game->GetLives() - 1);

			//dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
		}
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, turnRate);

	}
}