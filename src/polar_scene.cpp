#include "polar_scene.h"
#include "polar.h"

void polarScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
}

void polarScene::Update()
{
}

void polarScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, GRAY);
	//DrawArchimedeanSpiral(1.0f, 0.3f, 200);
	//DrawCardioid(2.0f, 200);
	//DrawLimacon(1.0f, 2.5f, 200);
	//DrawRoseCurve(3.0f, 15.0f, 200);
	//DrawLemniscate(2.0f, 200);

	m_camera->EndMode();
}

void polarScene::DrawGUI()
{
}

void polarScene::DrawArchimedeanSpiral(float radius, float spacing, int steps)
{
	float time = (float)GetTime();

	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (2 * PI);
		float r = radius + (spacing * theta);

		polar p{ time + theta, r };
		DrawCircle(p, 0.2f, PURPLE);
	}
}

void polarScene::DrawCardioid(float size, int steps)
{
	float time = (float)GetTime();

	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (2 * PI);
		float r = size * (1 + cos(theta));

		polar p{ time + theta, r };
		DrawCircle(p, 0.2f, PURPLE);
	}
}

void polarScene::DrawLimacon(float loop, float dimple, int steps)
{
	float time = (float)GetTime();

	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (2 * PI);
		float r = loop + (dimple * cos(theta));

		polar p{ time + theta, r };
		DrawCircle(p, 0.2f, PURPLE);
	}
}

void polarScene::DrawRoseCurve(float size, float petals, int steps)
{
	float time = (float)GetTime();

	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (2 * PI);
		float r = size * cos(petals * theta);

		polar p{ time + theta, r };
		DrawCircle(p, 0.2f, PURPLE);
	}
}

void polarScene::DrawLemniscate(float magnitude, int steps)
{
	float time = (float)GetTime();

	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (2 * PI);
		float r = (magnitude * magnitude) * cos(2 * theta);

		polar p{ time + theta, r };
		DrawCircle(p, 0.2f, PURPLE);
	}
}
