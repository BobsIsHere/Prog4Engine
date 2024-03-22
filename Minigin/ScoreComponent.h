#pragma once
#include <memory>
#include "UpdateComponent.h"

namespace dae
{
	class GameObject;
	class Observer; 
	class Subject;

	class ScoreComponent : public UpdateComponent
	{
	public:
		ScoreComponent(GameObject* gameObject);
		~ScoreComponent();

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		virtual void Update(float deltaTime) override; 

		void IncreaseScore(int amount);
		void SetScore(int amount);
		void AddObserver(Observer* observer);

		int GetScore() const;

	private:
		int m_Score;

		std::unique_ptr<Subject> m_pSubject;
	};
}