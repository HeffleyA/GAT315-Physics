#include "trigonometry_scene.h"

void TrigonometryScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
}

void TrigonometryScene::Update()
{
}

void TrigonometryScene::FixedUpdate()
{
}

float DegToRad(float degrees)
{
	return degrees * (PI / 180);
}

float RadToDeg(float radians)
{
	return radians * (180 / PI);
}


float Vector2Length(const Vector2& v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}


//Vector2 Vector2Normalize(const Vector2& v)
//{
//	//float l = Vector2Length(v);
//	if (l == 0) return Vector2{ 0, 0 };
//	return Vector2{ v.x / l, v.y / l };
//}

void TrigonometryScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);
	//DrawCircle(Vector2{ 0, 0 }, 1, RED);
	float radius = 3;
	float rate = 0.8f;
	float time = (float)GetTime() * rate;

	//circle
	int steps = 50;
	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (2 * PI); //0 - 1
		float x = cos(theta) * radius * 0.5f;
		float y = sin(theta) * radius;

		DrawCircle(Vector2{ x, y }, 0.25f, PURPLE);
	}

	// sin / cos
	for (float f = -10.0f; f < 10; f += 0.2f)
	{
		float theta = time + ((f / 18) * (2 * PI)); //0 - 1
		float c = cosf(theta) * radius;
		float s = sinf(theta) * radius;

		DrawCircle(Vector2{ f, c }, 0.25f, DARKPURPLE);
		DrawCircle(Vector2{ f, s }, 0.25f, DARKBLUE);
	}

	float theta = time;
	float x = cosf(theta) * radius;
	float y = sinf(theta) * radius;
	DrawCircle(Vector2{ x, y }, 0.25f, PINK);

	float angle = atan2(y, x);

	m_camera->EndMode();
}

void TrigonometryScene::DrawGUI()
{
}
