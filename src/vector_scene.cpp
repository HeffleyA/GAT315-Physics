#include "vector_scene.h"
#include "body.h"
#include "raymath.h"
#include "math_utils.h"

void VectorScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();

	//Body* body = new Body(Vector2{ 3, 0 }, Vector2{ 0, 0 }, 0.25f, WHITE);
	//m_head = body;
	//m_player = body;

	//for (int i = 0; i < 10; i++)
	//{
	//	body->next = new Body(Vector2{ randomf() * 5, randomf() * 5 }, Vector2{ 0, 0 }, 0.25f, RED);
	//	body->next->prev = body;
	//	body = body->next;
	//}
}

void VectorScene::Update()
{
	float dt = GetFrameTime();

	float theta = randomf(0, 360);

	if (IsMouseButtonPressed(0))
	{
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());

		for (int i = 0; i < 100; i++)
		{
			Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(360), 1, 1));
			float offset = randomf(0, 360);
			float x = cos(theta);
			float y = sin(theta);
			body->velocity = Vector2{ x, y } * randomf(1, 6);
		}
	}

	m_world->Step(dt);

	//// player control
	//Vector2 input{ 0, 0 };
	//if (IsKeyDown(KEY_A)) input.x = -1;
	//if (IsKeyDown(KEY_D)) input.x = 1;
	//if (IsKeyDown(KEY_W)) input.y = 1;
	//if (IsKeyDown(KEY_S)) input.y = -1;
	//input = Vector2Normalize(input);
	//m_player->velocity = input * 3;

	//Body* body = m_head;
	//while (body)
	//{
	//	if (body == m_player)
	//	{
	//		body->Step(dt);
	//		body = body->next;
	//		continue;
	//	}

	//	Vector2 direction = m_player->position - body->position;
	//	direction = Vector2Normalize(direction) * 1;
	//	body->velocity = direction;

	//	body->Step(dt);
	//	body = body->next;
	//}
}

void VectorScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGREEN);
	m_world->Draw(*this);

	//Body* body = m_head;
	//while (body)
	//{
	//	body->Draw(*this);
	//	body = body->next;
	//}

	m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
}
