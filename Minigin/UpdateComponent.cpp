#include "UpdateComponent.h"

dae::UpdateComponent::UpdateComponent(GameObject* pGameObject) :
	Component{ pGameObject }
{
}

dae::UpdateComponent::~UpdateComponent()
{
}

void dae::UpdateComponent::Render() const
{
}

void dae::UpdateComponent::RenderGui()
{
}

void dae::UpdateComponent::Update(float)
{
}