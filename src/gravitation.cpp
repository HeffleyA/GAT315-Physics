#include "body.h"
#include "raymath.h"
#include <vector>
#include <algorithm>

using bodies_t = std::vector<Body*>;

void ApplyGravitation(bodies_t& bodies, float strength)  
{  
   for (int i = 0; i < bodies.size(); i++)  
   {  
       Body* bodyA = bodies[i];  

       for (int j = i + 1; j < bodies.size(); j++)  
       {  
           Body* bodyB = bodies[j];  

           Vector2 direction = bodyA->position - bodyB->position;
           float distance = sqrt((direction.x * direction.x) + (direction.y * direction.y));
           distance = std::max(distance, 1.0f);
           float forceMagnitude = (bodyA->mass * bodyB->mass / (distance * distance)) * strength;
           Vector2 forceVector = Vector2Normalize(direction) * forceMagnitude;
           bodyA->ApplyForce(Vector2Negate(forceVector));
           bodyB->ApplyForce(forceVector);
       }  
   }  
}
