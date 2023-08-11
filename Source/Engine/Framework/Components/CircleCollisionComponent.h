#pragma once
#include "CollisionComponent.h"

namespace kda 
{
	class CircleCollisionComponent : public CollisionComponent
	{
		// Inherited via CollisionComponent
		virtual void Update(float dt) override;
		virtual bool CheckCollision(CollisionComponent* collision) override;
	};
}