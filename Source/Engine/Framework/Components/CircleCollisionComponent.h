#pragma once
#include "CollisionComponent.h"

namespace kda 
{
	class CircleCollisionComponent : public CollisionComponent
	{
	public:
		// Inherited via CollisionComponent
		CLASS_DECLARATION(CircleCollisionComponent)

		virtual void Update(float dt) override;
		virtual bool CheckCollision(CollisionComponent* collision) override;
	};
}