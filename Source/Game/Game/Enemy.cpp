#include "Enemy.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
void Enemy::Update(float dt)
{

	Player* player = scene->GetActorByName<Player>("Player");
    if (player) {
        viper::vec2 direction{ 1,0 };
		direction = player->m_transform.position - m_transform.position;
		direction = direction.Normalized();
		m_transform.rotation = viper::math::radToDeg(direction.Angle());
    }


    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(m_transform.rotation)) * speed;
    velocity += force * dt;

    m_transform.position.x = viper::math::wrap(m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    m_transform.position.y = viper::math::wrap(m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());

    Actor::Update(dt);
}
