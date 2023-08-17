#pragma once
#include "RenderComponent.h"
#include "Render/Model.h"
#include "Framework/Resource/Resource.h"

namespace kda {
	class ModelRenderComponent : public RenderComponent {
		public:
			CLASS_DECLARATION(ModelRenderComponent)

			bool Initialize() override;
			void Update(float dt) override;
			void Draw(class Renderer& renderer) override;

			virtual float GetRadius() override { return m_model->getRadius(); }
		public:
			std::string modelName;
			res_t<Model> m_model;
	};
}