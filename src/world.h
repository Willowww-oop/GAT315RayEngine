#pragma once
#include "raylib.h"
#include <vector>

struct Body;
class Scene;

class World
{
public:
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0, -9.81f}, size_t poolSize = 30);
	
	Body* CreateBody(const Vector2 position, float size, const Color& color);
	void Step(float dt);
	void Draw(const class Scene& scene);

	void DestroyAll();

	std::vector<Body*> GetBodies() { return m_bodies; }

	static Vector2 gravity;

private:

	std::vector<Body*> m_bodies;
};