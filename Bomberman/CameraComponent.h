#pragma once
#include "UpdateComponent.h"

namespace dae
{
	class GameObject;

	class CameraComponent final : public UpdateComponent
	{
	public:
		CameraComponent(GameObject* pGameObject, float mapWidth, float screenWidth, float playableArea);
		virtual ~CameraComponent();

		CameraComponent(const CameraComponent& other) = delete;
		CameraComponent(CameraComponent&& other) = delete;
		CameraComponent& operator=(const CameraComponent& other) = delete;
		CameraComponent& operator=(CameraComponent&& other) = delete;

		virtual void Update() override;

	private:
		GameObject* m_pGameObject;

		float m_ScreenWidth;
		float m_MapWidth;
		float m_PlayableAreaWidth;
	};
}