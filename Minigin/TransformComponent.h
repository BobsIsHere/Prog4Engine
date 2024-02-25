#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(std::weak_ptr<GameObject> pGameObject);
		virtual ~TransformComponent();

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		virtual void Update(float) override;
		virtual void Render() const override;

		void SetPosition(float x, float y, float z = 0);
		const glm::vec3& GetPosition() const { return m_Position; }

	private:
		glm::vec3 m_Position;
	};
}
