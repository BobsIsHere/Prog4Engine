#pragma once
#include <memory>
#include "UpdateComponent.h"

namespace dae
{
	class GameObject;
	class Observer; 
	class Subject;

	class HealthComponent : public UpdateComponent
	{
	public:
		HealthComponent(GameObject* gameObject);
		~HealthComponent();

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;

		void LowerLives(int amount);
		void AddObserver(Observer* observer);

		int GetLives() const;

	private:
		int m_Lives;

		std::unique_ptr<Subject> m_pSubject;
	};
}