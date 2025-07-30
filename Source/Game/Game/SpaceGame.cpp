#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Player.h"
#include "Core/Random.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Enemy.h"

#include <vector>
bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<viper::Scene>();

    std::vector<viper::vec2> points{
       { 5, 0 },
       { -2, 3 },
       { 0, 0 },
       { -2, -3 },
       { 5, 0}
    };

    std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(points, viper::vec3{ 0,0,1 });
    //viper::Model* model = new viper::Model{ points, viper::vec3{0,0,1} };

    //create player
    viper::Transform transform{viper::vec2 { viper::GetEngine().GetRenderer().GetWidth() * 0.5f, viper::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 10};
    std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
    player->speed = 1500.0f;
    player->rotationRate = 180.0f;
    player->damping = 1.5f;
	player->name = "Player";
    m_scene->AddActor(std::move(player));


    viper::Scene scene;
	//create enemies
    std::shared_ptr<viper::Model> enemyModel = std::make_shared<viper::Model>(points, viper::vec3{ 1.0f, 0.0f, 0.0f });
    for (int i = 0; i < 10; i++) {
        viper::Transform transform{ {viper::random::getReal() * viper::GetEngine().GetRenderer().GetWidth(), viper::random::getReal() * viper::GetEngine().GetRenderer().GetHeight()}, 0, 10 };
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
		enemy->damping = 1.5f;
        enemy->speed = (viper::random::getReal() * 800) + 500;
        m_scene->AddActor(std::move(enemy));
    }
         return false;
}

void SpaceGame::Update()
{
    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw()
{
    m_scene->Draw(viper::GetEngine().GetRenderer());
}

void SpaceGame::Shutdown()
{

}
