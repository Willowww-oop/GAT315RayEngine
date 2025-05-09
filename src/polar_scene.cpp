#include "polar_scene.h"
#include "raymath.h"

void polar_scene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void polar_scene::Update()
{
}

void polar_scene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);

	float rate = 2;
	float time = (float)GetTime() * rate;
	float radians = 180 * DEG2RAD;
	
	int steps = 50;

	DrawArchSpiral(2, 3, RED);

	m_camera->EndMode();
}

void polar_scene::DrawArchSpiral(float a, float b, Color& color)
{
	Polar p;
	float rate = 2;
	float time = (float)GetTime() * rate;
	float steps = 10 * 2 * PI;
	
	for (float x = 0.5f; x < steps; x++)
	{
		p.angle = x;
		p.radius = a + (b * p.angle);

		if (x > 1)
		{

		}

		DrawCircle(Vector2{ p.radius, p.angle }, 0.25f, color);
	}

}

void polar_scene::DrawCardioid(float a, Color& color)
{
}

void polar_scene::Limacon(float a, float b, Color& color)
{
}

void polar_scene::DrawRose(float a, float k, Color& color)
{
}

void polar_scene::DrawCustom(float a, float b, Color& color)
{
}

void polar_scene::DrawGUI()
{
}

