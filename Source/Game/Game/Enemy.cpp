#include "Enemy.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Framework/Game.h"
#include "Rocket.h"
#include "../GameData.h"
#include "Math/Vector3.h"
#include "Renderer/Model.h"
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

    fireTimer -= dt;
    if (fireTimer <= 0) {
        fireTimer = fireTime;

        std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::rocketPoints, viper::vec3{ 0,1,0 });
        viper::Transform transform{ this->m_transform.position, this->m_transform.rotation, 2.0f };
        auto rocket = std::make_unique<Rocket>(transform, model);
        rocket->speed = 500.0f;
        rocket->tag = "Enemy";
        rocket->name = "Rocket";
        scene->AddActor(std::move(rocket));
    }

    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
    if (tag != other->tag) {
        destroyed = true;
		scene->GetGame()->AddPoints(100);
       
    }
}
