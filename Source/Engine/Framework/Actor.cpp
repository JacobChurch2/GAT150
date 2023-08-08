#include "Actor.h"
#include "Components/RenderComponent.h"

namespace kda {
	void Actor::Update(float dt){
		if (m_lifespan != -1.0f) {

			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		for (auto& component : m_components) {
			component->Update(dt);
		}
	}

	void Actor::Draw(kda::Renderer& renderer){
		//m_model->Draw(renderer, m_transform);
		for(auto& component : m_components){
			if(dynamic_cast<RenderComponent*>(component.get())){
				dynamic_cast<RenderComponent*>(component.get())->Draw(renderer);
			}
		}
	}
	void Actor::AddComponent(std::unique_ptr<Component> component){
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}
}

