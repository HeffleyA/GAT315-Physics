#pragma once
#include "body.h"
#include "spring.h"
#include "contact.h"
#include "raylib.h"
#include <vector>

using bodies_t = std::vector<Body*>;
using springs_t = std::vector<Spring*>;
using contacts_t = std::vector<Contact>;

class World
{
public:
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0, -9.81f }, size_t poolSize = 30);

	Body* CreateBody(const Vector2& position, float size, const Color& color);
	Body* CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color);
	void Step(float timestep);
	void Draw(const Scene& scene);

	void DestroyAll();

	bodies_t& GetBodies() { return m_bodies; }

	Spring* CreateSpring(struct Body* bodyA, struct Body* bodyB, float restLength, float stiffness, float damping);

	inline static Vector2 gravity{ 0, -9.81f };
	inline static float gravitation = 0;
	inline static float springStiffnessMultiplier = 1;
	inline static bool simulate = true;

private:
	
	bodies_t m_bodies;
	springs_t m_springs;
	contacts_t m_contacts;

};