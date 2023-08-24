#include "Pew.h"
#include "Render/Render.h"
#include "Framework/Framework.h"

namespace kda {
	CLASS_DEFINITION(Pew)

	bool Pew::Initialize() 
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();

		auto collisionComponent = GetComponent<kda::CollisionComponent>();
		if (collisionComponent)
		{
			
		}

		return true;
	}

	void Pew::Update(float dt)
	{
		Actor::Update(dt);

		kda::vec2 forward = kda::vec2{ 0, -1 }.Rotate(transform.rotation);
		m_physicsComponent->SetVelocity(forward * speed);

		transform.position.x = kda::wrap(transform.position.x, (float)kda::g_renderer.GetWidth());
		transform.position.y = kda::wrap(transform.position.y, (float)kda::g_renderer.GetHeight());
	}

	void Pew::onCollisionEnter(Actor* actor) {
		if (actor->tag != tag) {
			lifespan = 0;
			destroyed = true;
		}
	}
	void Pew::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
	}
}
