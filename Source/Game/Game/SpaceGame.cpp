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
#include "Renderer/particleSystem.H"



#include <vector>
bool SpaceGame::Initialize()
{
    

	m_scene = std::make_unique<viper::Scene>(this);

    m_titleFont = std::make_shared<viper::Font>();
	m_titleFont->Load("ArcadeClassic.ttf", 128);

    m_uiFont = std::make_shared<viper::Font>();
    m_uiFont->Load("ArcadeClassic.ttf", 48);

    m_titleText = std::make_unique < viper::Text>(m_titleFont);
    m_scoreText = std::make_unique < viper::Text>(m_uiFont);
    m_livesText = std::make_unique < viper::Text>(m_uiFont);
    
	
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
		m_scene->RemoveAllActors();
        //create player
        std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 0,0,1 });
        viper::Transform transform{ viper::vec2 { viper::GetEngine().GetRenderer().GetWidth() * 0.5f, viper::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 10 };
        auto player = std::make_unique<Player>(transform, model);
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
            SpawnEnemy();
        
        }

        break;

    case SpaceGame::GameState::PlayerDead:
		m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_lives--;
            if (m_lives == 0) {
				m_stateTimer = 3.0f;
                m_gameState = GameState::GameOver;
            }
            else m_gameState = GameState::StartRound;
        }
        break;

    case SpaceGame::GameState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_gameState = GameState::Title;
		}   
        break;

    default:
        break;
    }
    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(viper::Renderer& renderer)
{
    if (m_gameState == GameState::Title) {
        m_titleText->Create(renderer, "PIT VIPER", viper::vec3{ 1, 0 ,0 });
        m_titleText->Draw(renderer, 350, 400);
    }

    if (m_gameState == GameState::GameOver) {
        m_titleText->Create(renderer, "GAME OVER", viper::vec3{ 1, 0 ,0 });
        m_titleText->Draw(renderer, 350, 400);
    }

    m_scoreText->Create(renderer, "SCORE " + std::to_string(m_score), {1,1,1});
    m_scoreText->Draw(renderer, 20, 20);

    m_livesText->Create(renderer, "LIVES " + std::to_string(m_lives), {1,1,1});
    m_livesText->Draw(renderer, renderer.GetWidth() - 200, 20);


    m_scene->Draw(renderer);
    
	viper::GetEngine().GetPS().Draw(renderer); 
}

void SpaceGame::OnPlayerDeath()
{
	m_gameState = GameState::PlayerDead;
	m_stateTimer = 2.0f;
}

void SpaceGame::SpawnEnemy()
{
    Player* player = m_scene->GetActorByName<Player>("Player");
    if (player) {
        //create enemies
        std::shared_ptr<viper::Model> enemyModel = std::make_shared<viper::Model>(GameData::enemyPoints, viper::vec3{ 1.0f, 0.0f, 0.0f });
               
       //spawn at random position away from player
        viper::vec2 position = player->m_transform.position * viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);

        viper::Transform transform{ position, viper::random::getReal(0.0f, 360.0f), 10};

        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
        enemy->damping = 1.5f;
        enemy->fireTime = 2;
        enemy->fireTimer = 3;
        enemy->speed = (viper::random::getReal() * 400) + 500;
        enemy->tag = "Enemy";
        m_scene->AddActor(std::move(enemy));
    }
    

}

void SpaceGame::Shutdown()
{

}
