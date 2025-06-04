#include "world.h"
#include "body.h"
#include "gravitation.h"
#include "collision.h"

World::~World()
{

}

void World::Initialize(Vector2 gravity, size_t poolSize)
{
	World::gravity = gravity;

	m_bodies.reserve(poolSize);
}

Body* World::CreateBody(const Vector2 position, float size, const Color& color)
{
	Body* body = new Body(position, size, color);
	m_bodies.push_back(body);

	return body;
}

Body* World::CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color)
{
	Body* body = new Body(type, position, mass, size, color);
	m_bodies.push_back(body);

	return body;
}

void World::Step(float dt)
{
	if (!simulate) return;

	if (gravitation > 0) ApplyGravitation(m_bodies, gravitation);

	for (auto spring : m_springs)
	{
		spring->ApplyForce(0.5f, 1.0f);
	}

	for (auto body : m_bodies)
	{
		body->Step(dt);
		body->ClearForce();
	}

	for (int i = 0; i < 10; i++)
	{
		m_contacts.clear();
		CreateContacts(m_bodies, m_contacts);
		SeparateContacts(m_contacts);
		ResolveContacts(m_contacts);
	}
}

void World::Draw(const Scene& scene)
{
	for (auto spring : m_springs)
	{
		spring->Draw(scene);
	}

	for (auto body : m_bodies)
	{
		body->Draw(scene);
	}
}

Spring* World::CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness)
{
	Spring* spring = new Spring(bodyA, bodyB, restLength, stiffness);
	m_springs.push_back(spring);

	return spring;
}

void World::DestroyAll()
{
	for (auto body : m_bodies)
	{
		delete body;
	}

	m_bodies.clear();

	for (auto spring : m_springs)
	{
		delete spring;
	}

	m_springs.clear();
}

