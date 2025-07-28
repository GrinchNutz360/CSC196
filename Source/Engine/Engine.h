#pragma once
#include "Core/Time.h"
#include <memory>


namespace viper {
	class Renderer;
	class AudioSystem;
	class InputSystem;


	class Engine {
	public:
		Engine() = default;

		bool Initialize();
		void Shutdown();

		void Update();
		void Draw();

		Renderer& GetRenderer() { return *m_renderer; }
		AudioSystem& GetAudio() { return *m_audio; }
		InputSystem& GetInput() { return *m_input; }

		Time& GetTime() { return m_time; }

	private:
		Time m_time;

		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<AudioSystem> m_audio;
		std::unique_ptr<InputSystem> m_input;

	};
	Engine& GetEngine();
	
}