#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>
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
		float intensity;
		float range;
		float innerAngle;
		float outerAngle;
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

		std::vector<light_t> m_lights;
		int numLights = 1;
		int m_selected = 0;
		glm::vec3 ambientLight{ 1,1,1 };

		Transform m_transform;
		res_t<Model> m_model;
		res_t<Material> m_material;
	};
}