#include "Component.h"

dae::Component::Component(GameObject* pGameObject) :
	m_pGameObject{ pGameObject }
{

}

dae::Component::~Component()
{

}

void dae::Component::Render() const
{
}

void dae::Component::Update()
{
} 

