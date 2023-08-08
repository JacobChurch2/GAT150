#pragma once
#include "Framework/Components/RenderComponent.h"
#include <Render/Texture.h>

namespace kda {
	class SpriteComponent : public RenderComponent {
		public:
			void Update(float dt) override;
			void Draw(class Renderer& renderer) override;
		public:
			res_t<Texture> m_texture;
	};
}