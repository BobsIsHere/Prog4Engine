#pragma once
#include "Component.h"

namespace dae
{
	class UpdateComponent : public Component
	{
	public:
		UpdateComponent(GameObject* pGameObject);
		virtual ~UpdateComponent();

		UpdateComponent(const UpdateComponent& other) = delete;
		UpdateComponent(UpdateComponent&& other) = delete;
		UpdateComponent& operator=(const UpdateComponent& other) = delete;
		UpdateComponent& operator=(UpdateComponent&& other) = delete;

		virtual void Update(float deltaTime) override = 0;
		virtual void RenderGui() override;
		virtual void Render() const override;
	};
}