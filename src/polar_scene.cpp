#include "polar_scene.h"
#include "raymath.h"

void polar_scene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void polar_scene::Update()
{
}

void polar_scene::FixedUpdate()
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

	DrawCustom(2.0f, 5.0f, RED);

	m_camera->EndMode();
}

void polar_scene::DrawArchSpiral(float a, float b, Color& color)
{
	Polar p;
	float rate = 2;
	float time = (float)GetTime() * rate;
	float steps = 10 * 2 * PI;
	Vector2 prevPoint = { 0 };
	
	for (float x = 0.1f; x < steps; x+= 0.1f)
	{
		p.angle = x;
		p.radius = a + (b * p.angle);

		Vector2 point = (Vector2)p;

		if (x > 1)
		{
			DrawLine(prevPoint, point, 2, PURPLE);
		}

		prevPoint = point;

		DrawCircle(point, 0.25f, color);

	}

}

void polar_scene::DrawCardioid(float a, Color& color)
{
	Polar p;
	float rate = 2;
	float time = (float)GetTime() * rate;
	float steps = 10 * 2 * PI;
	Vector2 prevPoint = { 0 };

	for (float x = 0.1f; x < steps; x+= 0.1f)
	{
		p.angle = x;
		p.radius = a * (1 + cosf(p.angle));

		Vector2 point = (Vector2)p;

		if (x > 1)
		{
			DrawLine(prevPoint, point, 2, PURPLE);
		}

		prevPoint = point;

		//rawCircle(point, 0.25f, color);
	}


}

void polar_scene::Limacon(float a, float b, Color& color)
{
	Polar p;
	float rate = 2;
	float time = (float)GetTime() * rate;
	float steps = 10 * 2 * PI;
	Vector2 prevPoint = { 0 };

	for (float x = 0.1f; x < steps; x += 0.1f)
	{
		p.angle = x;
		p.radius = a + (b * cosf(p.angle));

		Vector2 point = (Vector2)p;

		if (x > 1)
		{
			DrawLine(prevPoint, point, 2, PURPLE);
		}

		prevPoint = point;
	}
}

void polar_scene::DrawRose(float a, float k, Color& color)
{
	Polar p;
	float rate = 2;
	float time = (float)GetTime() * rate;
	float steps = 10 * 2 * PI;
	Vector2 prevPoint = { 0 };

	for (float x = 0.1f; x < steps; x += 0.1f)
	{
		p.angle = x;
		p.radius = a * cosf(k * p.angle);

		Vector2 point = (Vector2)p;

		if (x > 1)
		{
			DrawLine(prevPoint, point, 2, PURPLE);
		}

		prevPoint = point;
	}
}

void polar_scene::DrawCustom(float a, float b, Color& color)
{
	Polar p;
	float rate = 2;
	float time = (float)GetTime() * rate;
	float steps = 10 * 2 * PI;
	Vector2 prevPoint = { 0 };

	for (float x = 0.1f; x < steps; x += 0.1f)
	{
		p.angle = x;
		p.radius = (b * sinf(p.angle)) * (a * cosf(p.angle) + -tanf(p.angle));

		Vector2 point = (Vector2)p;

		if (x > 1)
		{
			DrawLine(prevPoint, point, 2, PURPLE);
		}

		prevPoint = point;
	}
}

void polar_scene::DrawGUI()
{
}

