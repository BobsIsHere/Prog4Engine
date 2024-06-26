#pragma once
#include "TextComponent.h"
#include "UpdateComponent.h"

namespace dae
{
	class FPSComponent final : public UpdateComponent
	{
	public:
		FPSComponent(GameObject* pGameObject);
		virtual ~FPSComponent();

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void Update() override;

	private:
		int m_FrameCount;
		float m_TotalTime;

		TextComponent* m_pTextComponent;
	};
}