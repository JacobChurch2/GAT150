#pragma once
#include "../Core/Core.h"
#include "../Render/Model.h"

namespace kda {
	class Actor
	{
	public:
		Actor() = default;

		Actor(const kda::Transform& transform, std::shared_ptr<kda::Model> model) :
			m_transform{ transform },
			m_model{ model }
		{}

		Actor(const kda::Transform& transform) : m_transform{ transform } {}

		virtual void Update(float dt);
		virtual void Draw(kda::Renderer& renderer);

		float GetRadius() { return (m_model) ? m_model->getRadius() * m_transform.scale : -10000; }
		virtual void OnCollision(Actor* other) {}

		void AddForce(vec2 force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

		kda::Transform m_transform;
		std::string m_tag;

		float m_lifespan = -1.0f;
	protected:
		bool m_destroyed = false;
		std::shared_ptr<Model> m_model;
		
		vec2 m_velocity;
		float m_damping = 0;
	};
}