#include "Enemy.h"
#include "Player.h"
#include "Pew.h"
#include "SpaceGame.h"
#include "Render/Renderer.h"
#include "Framework/Framework.h"

namespace kda {
	CLASS_DEFINITION(Enemy)

	bool Enemy::Initialize() {
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

	void Enemy::Update(float dt) {

		Actor::Update(dt);

		Player* player = m_scene->GetActor<Player>();
		kda::vec2 forward = kda::vec2{ 0, -1 }.Rotate(transform.rotation);

		if (player) {
			kda::Vector2 direction = player->transform.position - transform.position;
			float turnAngle = kda::vec2::SignedAngle(forward, direction.Normalized());
			transform.rotation = direction.angle() + kda::halfpi;
			m_physicsComponent->ApplyTorque(turnAngle);
		}


		m_physicsComponent->ApplyForce(forward * speed);
		//transform.position += forward * m_speed * kda::g_time.getDeltaTime();
		transform.position.x = kda::wrap(transform.position.x, (float)kda::g_renderer.GetWidth());
		transform.position.y = kda::wrap(transform.position.y, (float)kda::g_renderer.GetHeight());

		fireRate -= dt;
		if (fireRate <= 0) {
			//TODO::fix weapon
			/*auto weapon = INSTANTIATE(Pew, "Rocket");
			weapon->transform = { transform.position, transform.rotation + kda::DegreesToRadians(10.0f), 1 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));*/

			/*kda::Transform transform1{transform.position, transform.rotation, 1};
			std::unique_ptr<Pew> pew = std::make_unique<Pew>(400.0f, transform1);
			pew->tag = "Enemy";

			std::unique_ptr<kda::SpriteComponent> component = std::make_unique<kda::SpriteComponent>();
			component->m_texture = GET_RESOURCE(kda::Texture, "EnemyBullet.png", kda::g_renderer);
			pew->AddComponent(std::move(component));

			auto collisionComponent = std::make_unique<kda::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			pew->AddComponent(std::move(collisionComponent));

			pew->Initialize();
			m_scene->Add(std::move(pew));

			m_fireRate = m_fireTime;*/
		}

	}

	void Enemy::onCollision(Actor* actor) {
		//Player* p = dynamic_cast<Player*>(actor)
		if (actor->tag == "Player") {
			hp -= 5;
		}
		if (hp <= 0 && !destroyed)
		{
			kda::EventManager::Instance().DispatchEvent("AddPoints", 100);
			//m_game->AddPoint(100);
			destroyed = true;

			kda::EmitterData data;
			data.burst = false;
			data.burstCount = 50;
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
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
		//READ_DATA(value, fireTime);
		//READ_DATA(value, fireRate);
	}
}
