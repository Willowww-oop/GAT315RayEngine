#include "vector_scene.h"
#include "body.h"
#include "gravitation.h"
#include "world.h"
#include "gui.h"
#include "raymath.h"
#include "mathUtils.h"

void vector_scene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();

}

void vector_scene::Update()
{
	float dt = GetFrameTime();

	float theta = randomf(0, 360);
	
	if (IsMouseButtonPressed(0))
	{
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());

		for (int i = 0; i < 100; i++)
		{
			Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(360), 1, 1));
			float offset = randomf(-180, 180);
			float x = cosf((theta + offset) * DEG2RAD);
			float y = sinf((theta + offset) * DEG2RAD);

			body->velocity = Vector2{ x, y } *randomf(1, 6);
			//body->gravityScale = 0.5f;
			body->restitution = randomf(0.5f, 1.0f);
		}

	}

	// Apply collision

	for (auto body : m_world->GetBodies())
	{
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -body->restitution;
		}

		if (body->position.x < -9)
		{
			body-> position.x = -9;
			body->velocity.x *= -body->restitution;
		}

		if (body->position.x > 9)
		{
			body->position.x = 9;
			body->velocity.x = -body->restitution;
		}
	}

}

void vector_scene::FixedUpdate()
{
	// Apply force

	m_world->Step(Scene::fixedTimestep);
}

void vector_scene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, GRAY);

	m_world->Draw(*this);

	m_camera->EndMode();
}

void vector_scene::DrawGUI()
{
	GUI::Draw();
}
