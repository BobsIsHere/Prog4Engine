#pragma once
#include <glm/glm.hpp>
#include "GameActorCommand.h"

namespace dae
{
	class MovementCommand final : public GameActorCommand
	{
	public:
		MovementCommand(GameObject* actor, glm::vec3 direction, float speed);
		virtual ~MovementCommand();

		MovementCommand(const MovementCommand& other) = delete;
		MovementCommand(MovementCommand&& other) = delete;
		MovementCommand& operator=(const MovementCommand& other) = delete;
		MovementCommand& operator=(MovementCommand&& other) = delete; 

		virtual void Execute(float deltaTime) override;

	private:

		glm::vec3 m_Direction;
		float m_Speed;
	};
}