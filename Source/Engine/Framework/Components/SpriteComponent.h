#pragma once
#include "RenderComponent.h"
#include "Render/Texture.h"
#include "Framework/Factory.h"

namespace kda {
	class SpriteComponent : public RenderComponent {
		public:
			CLASS_DECLARATION(SpriteComponent)

			bool Initialize() override;
			void Update(float dt) override;
			void Draw(class Renderer& renderer) override;

		public:
			Rect source;
			std::string textureName;
			res_t<Texture> m_texture;
	};
}