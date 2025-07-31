#include "Actor.h"
#include "../Renderer/Model.h"

namespace viper {
	void viper::Actor::Update(float dt)
	{
		if(destroyed)return;

		if(lifeSpan != 0.0f) {
			lifeSpan -= dt;
			destroyed = lifeSpan <= 0;
		}

		m_transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}

	void viper::Actor::Draw(Renderer& renderer)
	{
		if (destroyed){
			return;
		}
		m_model->Draw(renderer, m_transform);
	}
	float Actor::GetRadius()
	{
		return (m_model) ? m_model->GetRadius() * m_transform.scale * 0.9f: 0.0f;
	}
}
