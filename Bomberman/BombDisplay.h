#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class BombDisplay final : public Component, public Observer
	{
	public:
		BombDisplay(GameObject* pGameObject);
		virtual ~BombDisplay();

		BombDisplay(const BombDisplay& other) = delete;
		BombDisplay(BombDisplay&& other) = delete;
		BombDisplay& operator=(const BombDisplay& other) = delete;
		BombDisplay& operator=(BombDisplay&& other) = delete;

		virtual void Update() {};
		virtual void Render() const {};

		virtual void Notify(GameObject* pGameObject, Event event) override; 
	};
}