#pragma once
#include <vector>
#include <memory>
#include <string>


namespace viper {
	class Actor;

	class Scene {
	public:
		Scene() = default;
		
		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr<Actor> actor);

		 Actor* GetActorByName(const std::string& name);

	private:
		std::vector<std::unique_ptr<Actor>> m_actors;


	};
}