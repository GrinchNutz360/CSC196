#include "Actor.h"
#include "../Renderer/Model.h"

namespace viper {
	void viper::Actor::Update(float dt)
	{

	}

	void viper::Actor::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}
}
