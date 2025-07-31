#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Player.h"
#include "Core/Random.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Enemy.h"
#include "Input/InputSystems.h"
#include "../GameData.h"


#include <vector>
bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<viper::Scene>();

   /* std::vector<viper::vec2> points{
       { 5, 0 },
       { -2, 3 },
       { 0, 0 },
       { -2, -3 },
       { 5, 0}
    };*/

    
    //viper::Model* model = new viper::Model{ points, viper::vec3{0,0,1} };

    


    viper::Scene scene;
	
         return false;
}

void SpaceGame::Update(float dt)
{
    switch (m_gameState)
    {   

    case SpaceGame::GameState::Initialize:
		m_gameState = SpaceGame::GameState::Title;

        break;

    case SpaceGame::GameState::Title:
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
		}
        break;

    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
		m_gameState = GameState::StartRound;
        break;

    case SpaceGame::GameState::StartRound:
    {
        //create player
        std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 0,0,1 });
        viper::Transform transform{ viper::vec2 { viper::GetEngine().GetRenderer().GetWidth() * 0.5f, viper::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 10 };
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
        player->speed = 1500.0f;
        player->rotationRate = 180.0f;
        player->damping = 1.5f;
        player->tag = "Player";
        player->name = "Player";
        m_scene->AddActor(std::move(player));
		m_gameState = GameState::Game;
    }
        break;
	
    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 4;
            //create enemies
            std::shared_ptr<viper::Model> enemyModel = std::make_shared<viper::Model>(GameData::enemyPoints, viper::vec3{ 1.0f, 0.0f, 0.0f });
            viper::Transform transform{ {viper::random::getReal() * viper::GetEngine().GetRenderer().GetWidth(), viper::random::getReal() * viper::GetEngine().GetRenderer().GetHeight()}, 0, 10 };
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
            enemy->damping = 1.5f;
            enemy->speed = (viper::random::getReal() * 800) + 500;
            enemy->tag = "Enemy";
            m_scene->AddActor(std::move(enemy));
        
        }

        break;

    case SpaceGame::GameState::PlayerDead:
        m_lives--;
        if(m_lives == 0) m_gameState = GameState::GameOver;
		else m_gameState = GameState::StartRound;
        break;

    case SpaceGame::GameState::GameOver:
        break;

    default:
        break;
    }
    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw()
{
    m_scene->Draw(viper::GetEngine().GetRenderer());
}

void SpaceGame::Shutdown()
{

}
