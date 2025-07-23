#include "Model.h"
#include "Renderer.h"
namespace viper{
	/// <summary>
	/// Draws the model by rendering lines between its points using the specified renderer.
	/// </summary>
	/// <param name="renderer">The Renderer object used to draw the model.</param>
	void Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale) {
		//check if points are empty, if so return
		if (m_points.empty()) return;

		renderer.SetColor(m_color.r, m_color.g, m_color.b);

		//iterate through points and draw lines between them
		for (int i = 0; i < m_points.size() - 1; i++) {
			vec2 p1 = (m_points[i].Rotate(rotation) * scale) + position;
			vec2 p2 = (m_points[i + 1].Rotate(rotation) * scale) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
}

