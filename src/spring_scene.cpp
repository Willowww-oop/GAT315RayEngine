#include "spring_scene.h"
#include "body.h"
#include "world.h"
#include "raymath.h"
#include "Gravitation.h"
#include "mathUtils.h"
#include "raygui.h"
#include "gui.h"
#include <iostream>
	
void spring_scene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();
}

void spring_scene::Update()
{
	float dt = GetFrameTime();

	GUI::Update();
	for (auto body : m_world->GetBodies())
	{
		AABB aabb = body->GetAABB();
		AABB worldAABB = m_camera->GetAABB();

		if ((aabb.min().y) < worldAABB.min().y)
		{
			float overlap = (worldAABB.min().y - aabb.min().y); // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
		else if ((aabb.max().y) > worldAABB.max().y)
		{
			float overlap = (worldAABB.max().y - aabb.max().y);  // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}

		if ((aabb.min().x) < worldAABB.min().x)
		{
			float overlap = (worldAABB.min().x - aabb.min().x); // calculate how far the body has penetrated beyond the world boundary
			body->position.x += 2 * overlap; // move the body back inside the world bounds
			body->velocity.x*= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
		else if (aabb.max().x > worldAABB.max().x)
		{
			float overlap = (worldAABB.max().x - aabb.max().x);  // calculate how far the body has penetrated beyond the world boundary
			body->position.x += 2 * overlap; // move the body back inside the world bounds
			body->velocity.x *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
	}

	if (IsKeyPressed(KEY_SPACE)) World::simulate = !World::simulate;


	if (!GUI::mouseOverGUI)
	{

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			Body::Type type = (Body::Type)GUI::TypePhysicsDropdownActive;
			std::cout << GUI::TypePhysicsDropdownActive << std::endl;

			Body* body = m_world->CreateBody(type, position, GUI::MassPhysicsSliderValue, GUI::SizePhysicsSliderValue, ColorFromHSV(randomf(360), 1, 1));

			body->gravityScale = 0.5f;

			body->restitution = GUI::RestitutionPhysicsSliderValue;
			body->gravityScale = GUI::GravityScaleSliderValue;

			body->ApplyForce(randomUnitCircle() * 10, Body::ForceMode::Velocity);

		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selectedBody = GUI::GetBodyInteract(position, m_world->GetBodies(), *m_camera);
		}

		if (m_selectedBody)
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_LEFT_CONTROL))
			{	
				if (m_selectedBody->type == Body::Type::Dynamic)
				{
					Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
					Spring::ApplyForce(position, *m_selectedBody, 0.2f, 15.0f, m_selectedBody->damping);
				}

			}
			else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				m_connectBody = GUI::GetBodyInteract(position, m_world->GetBodies(), *m_camera);
				if (m_connectBody == m_selectedBody) m_connectBody = nullptr;
			}
			else
			{
				if (m_selectedBody && m_connectBody)
				{
					float distance = Vector2Distance(m_selectedBody->position, m_connectBody->position);
					m_world->CreateSpring(m_selectedBody, m_connectBody, distance, 20);

				}
				m_selectedBody = nullptr;
				m_connectBody = nullptr;
			}
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
			body->position.x = -9;
			body->velocity.x *= -body->restitution;
		}

		if (body->position.x > 9)
		{
			body->position.x = 9;
			body->velocity.x = -body->restitution;
		}
	}

}

void spring_scene::FixedUpdate()
{
	m_world->Step(Scene::fixedTimestep);
}

void spring_scene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, GRAY);

	m_world->Draw(*this);

	if (m_selectedBody)
	{
		DrawCircleLine(m_selectedBody->position, m_selectedBody->size, YELLOW, 5);

		if (m_connectBody)
		{
			//DrawCircleLine
			DrawCircleLine(m_connectBody->position, m_connectBody->size, YELLOW, 5);
			DrawLine(m_selectedBody->position, m_connectBody->position, 3, GREEN);
		}
		else
		{
			DrawLine(m_selectedBody->position, m_camera->ScreenToWorld(GetMousePosition()), 3, RED);
		}
	}

	m_camera->EndMode();
}

void spring_scene::DrawGUI()
{
	GUI::Draw();
}