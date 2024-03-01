#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* pGameObject);
		virtual ~TransformComponent();

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		virtual void Update(float) override;
		virtual void Render() const override;

		void SetLocalPosition(float x, float y, float z = 0);
		void SetWorldPosition(float x, float y, float z = 0);

		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }

	private:
		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;
	};
}
