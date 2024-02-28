#pragma once
#include "TextComponent.h"
#include "UpdateComponent.h"

namespace dae
{
	class FPSComponent final : public UpdateComponent
	{
	public:
		FPSComponent(std::weak_ptr<GameObject> pGameObject);
		virtual ~FPSComponent();

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void Update(float deltaTime) override;

	private:
		int m_FrameCount;
		float m_TotalTime;

		std::shared_ptr<TextComponent> m_pTextComponent;
	};
}