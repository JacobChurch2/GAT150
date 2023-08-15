#include "SpriteComponent.h"
#include "../../Render/Render.h"
#include "../Actor.h"

namespace kda {
	CLASS_DEFINITION(SpriteComponent)

	void kda::SpriteComponent::Update(float dt){

	}

	void kda::SpriteComponent::Draw(Renderer& renderer){
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform);
	}
}

