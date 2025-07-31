#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../Core/StringHelper.h"
#include <list>

namespace viper {
	class Actor;
	class Game;

	class Scene {
	public:
		Scene(Game* game) : m_game{ game } {};
		
		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveAllActors();

		template<typename T = Actor>
		 T* GetActorByName(const std::string& name);

		 template<typename T = Actor>
		 std::vector<T*> GetActorsByTag(const std::string& tag);

		 Game* GetGame() { return m_game; }

	private:
		Game* m_game{ nullptr };
		std::list<std::unique_ptr<Actor>> m_actors;


	};
	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors) {
			if (viper::tolower(actor->name) == viper::tolower(name)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					return object;
				}
			}
		}
		return nullptr;
	}
	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag)
	{
		std::vector<T*> results;
		for (auto& actor : m_actors) {
			if (viper::tolower(actor->tag) == viper::tolower(tag)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					results.push_back(object);
				}
			}
		}

		return results;
	}
}