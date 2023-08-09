#pragma once
#include "Core/Core.h"
#include "Framework/Resource/Resource.h"
#include <vector>

namespace kda {

	class Renderer;

	class Model : public Resource{
	public:
		Model() = default;

		Model(const std::vector<vec2>& points) : m_points{ points }{}

		bool Create(std::string filename, ...);
		bool load(const std::string& filename);

		void Draw(Renderer& renderer, const vec2& position, float scale, float rotation);
		void Draw(Renderer& renderer, const Transform& transform);
		float getRadius();

	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius = 0;
	};
}