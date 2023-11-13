#include "RotateComponent.h"
#include "Framework/Actor.h"
#include <Core/Math/Transform.h>

namespace nc {
	CLASS_DEFINITION(RotateComponent)

	bool RotateComponent::Initialize()
	{
		return true;
	}

	void RotateComponent::Update(float dt) {
		m_owner->transform.euler += euler * dt;

		glm::quat rotation = EulerToQuaternion(euler * dt);
		m_owner->transform.rotation = m_owner->transform.rotation * rotation;
	}

	void RotateComponent::ProcessGui() {
		ImGui::DragFloat3("Rotate", glm::value_ptr(euler));
	}

	void RotateComponent::Read(const json_t& value) {
		READ_NAME_DATA(value, "Rotate", euler);
	}
}