#include "body.h"
#include "world.h"
#include "raymath.h"
#include "integrator.h"

void Body::Step(float dt)
{
	if (type != Type::Dynamic) return;
	
	// apply gravity
	force += (World::gravity * gravityScale) * mass;
	// compute acceleration
	acceleration = (force * invMass);

	SemiImplicitIntegrator(*this, dt);
}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
	//scene.DrawText("%", position, 25, color);
}

void Body::ApplyForce(const Vector2& force, ForceMode forceMode)
{
	switch (forceMode)
	{
	case Body::ForceMode::Force:
		this->force += force;
		break;
	case Body::ForceMode::Impulse:
		this->velocity += force * invMass;
		break;
	case Body::ForceMode::Velocity:
		this->velocity += force;
		break;
	default:
		break;
	}
}
