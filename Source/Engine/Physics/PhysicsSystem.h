#pragma once
#include "Framework/Singleton.h"
#include "../ThirdParty/box2d/Include/b2_world.h"
#include <memory>
namespace kda
{
	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
	public:
		bool Initialize();
		void Update(float dt);

		friend class Singleton;
	private:
		PhysicsSystem() = default;
	private:
		std::unique_ptr<b2World> m_world;
	};
}
