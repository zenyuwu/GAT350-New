#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
//#include "Renderer/Material.h"
#include "Core/Math/Transform.h"
#include "Framework/Actor.h"
#include <vector>
#include <list>

#define POINT 0 //isn't supposed to be here??

namespace nc
{
	class World05 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time = 0;
		float m_speed = 5;

		glm::vec3 ambientColor{ 1,1,1 };
		//std::list<std::unique_ptr<Actor>> m_actors;
	};
}