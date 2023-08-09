#pragma once
#include "RenderComponent.h"
#include "Render/Model.h"
#include "Framework/Resource/Resource.h"

namespace kda {
	class ModelRenderComponent : public RenderComponent {
		public:
			void Update(float dt) override;
			void Draw(class Renderer& renderer) override;
		public:
			res_t<Model> m_model;
	};
}