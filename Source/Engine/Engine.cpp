#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystems.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.H"


namespace viper {

	Engine& GetEngine()
	{
		static Engine engine;
		return engine;
	}


	bool Engine::Initialize() {
		m_renderer = std::make_unique<viper::Renderer>();
		m_renderer->Initialize();
		m_renderer->CreateWinow("Viper Engine", 1200, 1024);

		m_input= std::make_unique<viper::InputSystem>();
		m_input->Initialize();

		m_audio= std::make_unique<viper::AudioSystem>();
		m_audio->Initialize();

		m_particleSystem = std::make_unique<viper::ParticleSystem>();
		m_particleSystem->Initialize(5000);

		return true;
	}

	void Engine::Shutdown() {
		m_particleSystem->Shutdown();
		m_audio->Shutdown();
		m_renderer->Shutdown();
		m_input->Shutdown();
	}
	
	void Engine::Update() {
		m_time.Tick();
		m_input->Update();
		m_audio->Update();
		m_particleSystem->Update(m_time.GetDeltaTime());
	}
	void Engine::Draw()
	{

	}
}