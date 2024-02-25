#include "UpdateComponent.h"

dae::UpdateComponent::UpdateComponent(std::weak_ptr<GameObject> pGameObject) :
	Component{pGameObject}
{
}

dae::UpdateComponent::~UpdateComponent()
{
}

void dae::UpdateComponent::Render() const
{
}

void dae::UpdateComponent::Update(float)
{
}
