#pragma once
#include "Object.h"
#include "../Core/Core.h"
#include "../Render/Model.h"
#include "Components/Component.h"
#include <memory>


namespace kda {
	class Actor : public Object {
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;
		Actor(const kda::Transform& transform) :
			transform{ transform }
		{}
		Actor(const Actor& other);

		virtual bool Initialize() override;
		virtual void OnDestroy() override;
		
		virtual void Update(float dt);
		virtual void Draw(kda::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();
		
		float GetRadius() { return 30.0f; }
		virtual void onCollision(Actor* other) {}
			
		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;
			
	public:
		kda::Transform transform;
		std::string tag;
			
		float lifespan = -1.0f;
		bool destroyed = false;
		bool persistent = false;
		bool prototype = false;

	protected:
		std::vector<std::unique_ptr<class Component>> components;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components) {
			T* result = dynamic_cast<T*>(component.get());
			if (result) {
				return result;
			}
		}
		return nullptr;
	}
}
