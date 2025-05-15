#include "body.h"
#include "intergrator.h"
#include "world.h";
#include "scene.h"
#include "raymath.h"

void Body::Step(float dt)
{
	if (type != Type::Dynamic) return;

	// Apply gravity

	force += (World::gravity * gravityScale) * mass;

	// Compute acceleration

	acceleration = (force * invMass);

	SemiImplicitIntegrator(*this, dt);

	
}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
}

void Body::ApplyForce(const Vector2 force)
{
	this->force = force;
}
