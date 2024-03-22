#pragma once
#include <memory>
#include "Subject.h"
#include "UpdateComponent.h"

namespace dae
{
	class GameObject;

	class CounterComponent : public UpdateComponent
	{
	public:
		CounterComponent(GameObject* gameObject);
		~CounterComponent();

		CounterComponent(const CounterComponent& other) = delete;
		CounterComponent(CounterComponent&& other) = delete;
		CounterComponent& operator=(const CounterComponent& other) = delete;
		CounterComponent& operator=(CounterComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;
		
		void Increment(int amount);
		void Decrement(int amount);
		void SetValue(int amount);
		void AddObserver(Observer* observer);

		int GetValue() const;

	private:
		int m_Value;
		int m_MaxValue;

		std::unique_ptr<Subject> m_pSubject;
	};
}