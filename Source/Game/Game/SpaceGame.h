#pragma once

#include "Framework/Game.h"

class SpaceGame : public viper::Game {
public: 
	enum class GameState {
		Initialize,
		Title, 
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameOver,
	};
public:
	SpaceGame() = default;

	bool Initialize() override;
	void Shutdown() override;

	void Update(float dt) override;
	void Draw() override;

private:
	GameState m_gameState = GameState::Initialize;
	float m_enemySpawnTimer{ 0 };
};