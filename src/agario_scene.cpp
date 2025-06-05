#include "agario_scene.h"
#include "world.h"
#include <iomanip>

void AgarioScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();

	Vector2 position = m_camera->ScreenToWorld(Vector2{ 640, 360 });
	m_playerbody = m_world->CreateBody(position, 0.1f, PURPLE);
	m_playerbody->type = Body::Type::Kinematic;
}

void AgarioScene::Update()
{
	float dt = GetFrameTime();
	timer -= dt;

	if (timer <= 0)
	{
		Vector2 position = m_camera->ScreenToWorld(Vector2{ randomf(1280.0f), randomf(720.0f) });
		Body::Type type = Body::Type::Dynamic;

		if (m_playerbody != nullptr)
		{
			float maxSize = m_playerbody->size;
			Body* body = m_world->CreateBody(type, position, randomf(1.0f, 10.0f), randomf(0.01f, maxSize *= 1.25f), ColorFromHSV(randomf(360), 1, 1));

			body->gravityScale = randomf(0.5f, 1.0f);
			body->restitution = randomf(0.5f, 1.0f);
			body->damping = randomf(0.2f, 1.0f);

			body->ApplyForce(randomOnUnitCircle() * 10, Body::ForceMode::Velocity);
		}

		timer = 2.0f;
	}

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
			body->position.x = worldAABB.min().x; //<update x>
		}
		else if (aabb.max().x > worldAABB.max().x)
		{
			body->position.x = worldAABB.max().x; //<update x>
		}

		if (score >= 1.0f && body != m_playerbody)
		{
			body->size = 0;
			body = nullptr;
		}
	}

	if (m_playerbody != nullptr)
	{
		if (IsKeyDown(KEY_W)) m_playerbody->position.y += dt;
		if (IsKeyDown(KEY_S)) m_playerbody->position.y -= dt;
		if (IsKeyDown(KEY_D)) m_playerbody->position.x += dt;
		if (IsKeyDown(KEY_A)) m_playerbody->position.x -= dt;
	}

	if (score >= 1.0f && m_playerbody != nullptr)
	{
		m_playerbody->size = 0;
		m_playerbody = nullptr;
	}
}

void AgarioScene::FixedUpdate()
{
	//apply forces
	if (m_playerbody != nullptr)
	{
		m_world->Step(Scene::fixedTimestep, m_playerbody);
	}
}

void AgarioScene::Draw()
{
	m_camera->BeginMode();
	DrawGrid(10, 5, DARKGREEN);
	m_world->Draw(*this);
	m_camera->EndMode();
}

#include <sstream> // Include necessary header for stringstream

void AgarioScene::DrawGUI()
{
	std::string scoreText;

   // Convert the score to a string with 2 decimal precision
	if (m_playerbody != nullptr)
	{
		std::ostringstream stream;
		stream << std::fixed << std::setprecision(2) << m_playerbody->size;
		scoreText = stream.str();

		score = m_playerbody->size;
	}

   // Draw the score text
   DrawText("Score: " + scoreText, m_camera->ScreenToWorld(Vector2{ 1450, 345 }), 20, RED);

   if (score >= 1.0f)
   {
	   DrawText("You Win!", m_camera->ScreenToWorld(Vector2{ 950, 150 }), 100, BLUE);
   }
}
