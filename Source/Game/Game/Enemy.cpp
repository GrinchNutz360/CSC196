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
#include "Renderer/ParticleSystem.H"
#include "Core/Random.h"

void Enemy::Update(float dt)
{
    bool playerSeen = false;

	Player* player = scene->GetActorByName<Player>("Player");
    if (player) {
        viper::vec2 direction{ 1,0 };
		direction = player->m_transform.position - m_transform.position;
		
        direction = direction.Normalized();
        viper::vec2 forward = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(m_transform.rotation));
        
        float angle = viper::vec2::SignedAngleBetween(forward, direction);
        angle = viper::math::sign(angle);
        m_transform.rotation += viper::math::radToDeg(angle * 5 * dt);

        angle = viper::math::radToDeg(viper::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 30;
    }



    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(m_transform.rotation)) * speed;
    velocity += force * dt;

    m_transform.position.x = viper::math::wrap(m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    m_transform.position.y = viper::math::wrap(m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());

    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
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
        for (int i = 0; i < 100; i++) {
            viper::Particle particle;
            particle.position = m_transform.position;
            particle.velocity = viper::random::onUnitCircle() * viper::random::getReal(10.0f, 200.0f);
            particle.color = viper::vec3{ 1,1,1 };
            particle.lifeSpan = 2;
            viper::GetEngine().GetPS().AddParticle(particle);
        }
       
    }
}
