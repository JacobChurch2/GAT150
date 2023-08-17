#include "Pew.h"
#include "Render/Render.h"
#include "Framework/Framework.h"

namespace kda {
	bool Pew::Initialize() {

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

	void Pew::Update(float dt) 
	{
		kda::vec2 forward = kda::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * kda::g_time.getDeltaTime();
		transform.position.x = kda::wrap(transform.position.x, (float)kda::g_renderer.GetWidth());
		transform.position.y = kda::wrap(transform.position.y, (float)kda::g_renderer.GetHeight());
	}

	void Pew::onCollision(Actor* actor) {
		if (actor->tag != tag) {
			lifespan = 0;
			destroyed = true;
		}
	}
	void Pew::Read(const json_t& value)
	{
		READ_DATA(value, speed);
	}
}
