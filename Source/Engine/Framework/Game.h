#pragma once
#include <memory>

namespace viper {
	class Game {
	public:
		Game() = default;

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;


	protected:
		int m_score{ 0 };
		int m_lives{ 0 };

		std::unique_ptr<class Scene> m_scene;

	};
}
