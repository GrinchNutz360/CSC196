#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Player.h"
#include "Core/Random.h"
#include "Engine.h"

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

    viper::Scene scene;

    for (int i = 0; i < 10; i++) {
        viper::Transform transform{ {viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024}, 0, 10 };
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
        m_scene->AddActor(std::move(player));
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
