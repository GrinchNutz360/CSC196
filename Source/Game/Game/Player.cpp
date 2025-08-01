#include "Player.h"
#include "Engine.h"
#include "Input/InputSystems.h"
#include "Renderer/Renderer.h"
#include "../GameData.h"
#include "Math/Vector3.h"
#include "Framework/Scene.h"
#include "Rocket.h"
#include "Core/Random.h"
#include"Renderer/ParticleSystem.H"
#include "Renderer/Model.h"
#include "SpaceGame.h"
#include "Audio/AudioSystem.h"

void Player::Update(float dt)
{
    viper::Particle particle;
    particle.position = m_transform.position;
    particle.velocity = viper::vec2{ viper::random::getReal(-200.0f, 200.0f), viper::random::getReal(-200.0f, 200.0f) };
    particle.color = viper::vec3{ 1,1,1 };
    particle.lifeSpan = 2;
    //viper::GetEngine().GetPS().AddParticle(particle);

    //rotation
    float rotate = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    m_transform.rotation += (rotate * rotationRate) * dt;

    //thrust
    float thrust = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Z) && viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +3;


    viper::vec2 direction{ 1,0 };
    viper::vec2 force = direction.Rotate(viper::math::degToRad(m_transform.rotation)) * thrust * speed;
    velocity += force * dt;

    m_transform.position.x = viper::math::wrap(m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    m_transform.position.y = viper::math::wrap(m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());

    //check fire key pressed
    //spawn rocket at player position and rotation
    fireTimer -= dt;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
        fireTimer = fireTime;
        viper::GetEngine().GetAudio().PlaySound("laser");

        std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::rocketPoints, viper::vec3{ 1,1,1 });
        viper::Transform transform{ this->m_transform.position, this->m_transform.rotation, 2.0f };
        auto rocket = std::make_unique<Rocket>(transform, model);
        rocket->speed = 1500.0f;
        rocket->tag = "Player";
        rocket->name = "Rocket";
        fireTimer = 1;
        scene->AddActor(std::move(rocket));
    }

    //fire machine gun
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_C)) {

        viper::GetEngine().GetAudio().PlaySound("machineGun");
        std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::rocketPoints, viper::vec3{ 157,0,255 });
        viper::Transform transform{ this->m_transform.position, this->m_transform.rotation, 2.0f };
        auto rocket = std::make_unique<Rocket>(transform, model);
        rocket->speed = 1500.0f;
        rocket->tag = "Player";
        rocket->name = "Rocket";
        scene->AddActor(std::move(rocket));

    }

    //fire shotgun
    fireTimer -= dt;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_V) && fireTimer <= 0) {
        fireTimer = fireTime;
        std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::rocketPoints, viper::vec3{ 1,0,0 });
        viper::GetEngine().GetAudio().PlaySound("shotGun");
        //viper::Transform transform{ this->m_transform.position, viper::random::getReal(this->m_transform.rotation + 20.0f, this->m_transform.rotation -20.0f), 2.0f};
        for (int i = 0; i < 10; i++) {
            // Assume you have some base rotation:
            float baseRotation = this->m_transform.rotation;

            // Add random spread, e.g., ±15 degrees
            float spread = viper::random::getReal(-15.0f, 15.0f);

            float newRotation = baseRotation + spread;

            viper::Transform transform{
                this->m_transform.position,
                newRotation,
                2.0f
            };

            auto rocket = std::make_unique<Rocket>(transform, model);
            rocket->speed = 1500.0f;
            rocket->tag = "Player";
            rocket->name = "Rocket";
            fireTimer = 3;
            scene->AddActor(std::move(rocket));


        }
    }

    //explosive
    fireTimer -= dt;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_O)&& viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_P)) {
        viper::GetEngine().GetAudio().PlaySound("nuke");
        std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::rocketPoints, viper::vec3{ 255, 165, 0 });
        viper::Transform transform{ this->m_transform.position, this->m_transform.rotation, 2000.0f };
        auto rocket = std::make_unique<Rocket>(transform, model);
        rocket->speed = 1500.0f;
        rocket->tag = "Rocket";
        rocket->name = "Rocket";
        scene->AddActor(std::move(rocket));
    }



        Actor::Update(dt);
}


   void Player::OnCollision(Actor * other)
    {
        if (tag != other->tag) {
            destroyed = true;
            dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDeath();
        }
    }
