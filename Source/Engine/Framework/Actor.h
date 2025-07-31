#pragma once
#include "../Math/Transform.h"
#include <memory>
#include <string>

namespace viper {
	class Actor {
	public:
		std::string name;
		std::string tag;


		vec2 velocity{ 0, 0 };
		float damping{ 0.2f };

		bool destroyed{ false };
		float lifeSpan{ 0.0f };

		class Scene* scene{ nullptr };


	public:
		Actor() = default;
		Actor(const Transform& transform, std::shared_ptr<class Model> model) :
			m_transform{ transform } 
			, m_model{ model }
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

		Transform& GetTransform() { return m_transform; }

	public:
		Transform m_transform;
		std::shared_ptr<Model> m_model;
		
	};
}