#include "Actor.h"
#include "../Renderer/Model.h"

namespace viper {
	void viper::Actor::Update(float dt)
	{

		m_transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}

	void viper::Actor::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}
}
