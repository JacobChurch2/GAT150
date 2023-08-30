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
			bool flipH = false;
			vec2 origin{ 0.5f, 0.5f };

			std::string textureName;
			res_t<Texture> m_texture;
	};
}