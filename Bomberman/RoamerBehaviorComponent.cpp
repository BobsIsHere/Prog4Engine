#include <memory>

#include "RoamerBehaviorComponent.h"
#include "MovementCommand.h"
#include "DeltaTime.h"

dae::RoamerBehaviorComponent::RoamerBehaviorComponent(GameObject* pGameObject, const float speed) :
	EnemyBehaviorComponent(pGameObject, speed)
{
}

dae::RoamerBehaviorComponent::~RoamerBehaviorComponent()
{
}
