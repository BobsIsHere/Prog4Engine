#include "RenderComponent.h"

dae::RenderComponent::RenderComponent(std::weak_ptr<GameObject> pGameObject) :
	Component{pGameObject}
{
}

dae::RenderComponent::~RenderComponent()
{
}

void dae::RenderComponent::Render() const
{
}

void dae::RenderComponent::Update(float)
{
}
