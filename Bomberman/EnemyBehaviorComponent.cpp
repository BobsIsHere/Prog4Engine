#include "EnemyBehaviorComponent.h"
#include "MovementCommand.h"
#include "DeltaTime.h"

dae::EnemyBehaviorComponent::EnemyBehaviorComponent(GameObject* pGameObject, const float speed) :
	UpdateComponent(pGameObject),
	m_Speed{ speed },
	m_AccumulatedTime{},
	m_SwitchTime{ 5.f },
	m_MoveDirection{}
{
	srand(static_cast<unsigned int>(time(nullptr)));
}

dae::EnemyBehaviorComponent::~EnemyBehaviorComponent()
{
}

void dae::EnemyBehaviorComponent::Update()
{
	m_AccumulatedTime += DeltaTime::GetInstance().GetDeltaTime();

	if (m_AccumulatedTime >= m_SwitchTime)
	{
		RandomizeDirection();
		m_AccumulatedTime = 0.f;
	}

	Move();
}

void dae::EnemyBehaviorComponent::SetDirection(const glm::vec3& direction)
{
	m_MoveDirection = direction;
}

void dae::EnemyBehaviorComponent::Move()
{
	const std::unique_ptr<MovementCommand> movementCommand{ std::make_unique<MovementCommand>(GetGameObject(), m_MoveDirection, m_Speed) };
	movementCommand->Execute();
}

void dae::EnemyBehaviorComponent::RandomizeDirection()
{
	const int amountOfDirections{ 4 };

	const glm::vec3 directions[amountOfDirections] = { { -1, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, -1, 0 } };
	m_MoveDirection = directions[rand() % amountOfDirections]; 
}
