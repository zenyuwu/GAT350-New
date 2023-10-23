#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
//#include "Renderer/Material.h"
#include "Core/Math/Transform.h"
#include <vector>

#define POINT 0

namespace nc
{


	struct light_t
	{
		enum eType
		{
			Point,
			Directional,
			Spot
		};
		eType type;
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 color;
		float cutoff;
	};

	class World04 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time = 0;
		float m_speed = 5;

		light_t m_light;
		glm::vec3 ambientLight{ 1,1,1 };

		Transform m_transform;
		res_t<Model> m_model;
	};
}