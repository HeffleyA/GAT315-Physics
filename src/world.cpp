#include "world.h"
#include "body.h"
#include "gravitation.h"
#include "gui.h"
#include "collision.h"

World::~World()
{
}

void World::Initialize(Vector2 gravity, size_t poolSize)
{
    World::gravity = gravity;
    m_bodies.reserve(poolSize);
}

Body* World::CreateBody(const Vector2& position, float size, const Color& color)
{
    Body* body = new Body(position, size, color);
    m_bodies.push_back(body);

    return body;
}

Body* World::CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color)
{
    Body* body = new Body(type, position, mass, size, color);
    m_bodies.push_back(body);

    return body;
}

void World::RemoveBody(Body* body)
{
    body->size = 0;
}

void World::Step(float timestep, Body* player)
{
    if (!simulate) return;

    for (auto spring : m_springs)
    {
        spring->ApplyForce(springStiffnessMultiplier);
    }

    if (gravitation > 0 ) ApplyGravitation(m_bodies, gravitation);

    for (auto body : m_bodies)
    {
        body->Step(timestep);
        body->ClearForce();
    }

    m_contacts.clear();
    CreateContacts(m_bodies, m_contacts);
    ResolveContacts(m_contacts, player);
    SeparateContacts(m_contacts);
}

void World::Draw(const Scene& scene)
{
    for (auto body : m_bodies)
    {
        body->Draw(scene);
    }
}

void World::DestroyAll()
{
    for (auto body : m_bodies)
    {
        delete body;
    }
}

Spring* World::CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness, float damping)
{
    Spring* spring = new Spring(bodyA, bodyB, restLength, stiffness, damping);
    m_springs.push_back(spring);

    return spring;
}
