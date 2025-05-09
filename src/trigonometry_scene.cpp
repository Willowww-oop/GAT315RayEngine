#include "trigonometry_scene.h"

void trigonometry_scene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void trigonometry_scene::Update()
{
}

float DegToRad(float degrees)
{
	return degrees * PI / 180;
}

float RadToDeg(float radians)
{
	return radians * 180/PI;
}

float Vector2Length(const Vector2& v)
{
	return sqrtf((v.x * v.x) + (v.y * v.y));
}


Vector2 Vector2Normalize(const Vector2& v)
{
	float l = Vector2Length(v);
	if (l == 0) return Vector2{ 0, 0 };
	return Vector2{ v.x / l, v.y / l };
}

void trigonometry_scene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);
	//DrawCircle(Vector2{ 0, 0 }, 1, RED);

	// Circle :3

	float radius = 3;
	float rate = 2;
	float time = (float)GetTime() * rate;
	float radians = 180 * DEG2RAD;

	int steps = 50;
	for (int i = 0; i < steps; i++)
	{
		float theta = i / float(steps) * (2 * PI); // 0 - 1
		float x = cosf(theta) * radius;
		float y = sinf(theta) * radius;

		DrawCircle(Vector2{ x, y }, 0.25f, RED);
	}

	// sin / cos

	for (float x = -10; x < 10; x += 0.2f)
	{
		float theta = time + (x / 10) * (2 * PI); // 0 - 1

		float c = cos(theta) * radius;
		float s = sin(theta) * radius;

		DrawCircle(Vector2{ x, c }, 0.25f, BLUE);
		DrawCircle(Vector2{ x, s }, 0.25f, PURPLE);
	}

	float theta = time;
	float x = cosf(theta) * radius;
	float y = sinf(theta) * radius;
	DrawCircle(Vector2{ x, y }, 0.25f, ORANGE);

	float angle = atan2(y, x);

	m_camera->EndMode();
}

void trigonometry_scene::DrawGUI()
{
}
