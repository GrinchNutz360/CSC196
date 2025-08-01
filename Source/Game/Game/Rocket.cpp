#include "Rocket.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
void Rocket::Update(float dt)
{
    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(m_transform.rotation)) * speed;
    velocity = force;

    //m_transform.position.x = viper::math::wrap(m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    //m_transform.position.y = viper::math::wrap(m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());

    Actor::Update(dt);
}

void Rocket::OnCollision(Actor* other)
{
    if (tag != other->tag && tag != "Rocket") {
        destroyed = true;
    }
 
}
