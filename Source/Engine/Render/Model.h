#pragma once
#include "Core/Core.h"
#include "Render.h"
#include <vector>

namespace kda
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {}

		bool Load(const std::string& filename);
		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);
		float getRadius();
	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius = 0;
	};
}