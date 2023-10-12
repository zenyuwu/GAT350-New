#pragma once
#include "Framework/World.h"
#include "Core/Math/Vector2.h"
#include <vector>

namespace nc
{
	class World01 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_angle = 0;
		float m_time;
		vec2 m_position;
		float m_scale = 0;
		//for hw stuff?
		std::vector<vec2> m_positions;
	};
}