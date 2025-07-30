#include "Scene.h"
#include "Actor.h"
#include "../Core/StringHelper.h"
#include "../Renderer/Renderer.h"


namespace viper {
	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float dt) {
		for (auto& actor : m_actors) {
			actor->Update(dt);

		}
	}

	/// <summary>
	/// Draws all actors in the scene using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actors.</param>
	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			actor->Draw(renderer);

		}
	}

	/// <summary>
	/// Adds an actor to the scene by transferring ownership.
	/// </summary>
	/// <param name="actor">A unique pointer to the actor to be added.</param>
	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		actor->scene = this;
		m_actors.push_back(std::move(actor));
	}
	Actor* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors) {
			if (tolower(actor->name) == tolower(name)) {
				return actor.get();
			}
		}
		return nullptr;
	}
} 