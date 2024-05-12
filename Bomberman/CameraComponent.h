#pragma once
#include "UpdateComponent.h"

namespace dae
{
	class GameObject;

	class CameraComponent final : public UpdateComponent
	{
	public:
		CameraComponent(GameObject* pGameObject); 
		virtual ~CameraComponent();

		CameraComponent(const CameraComponent& other) = delete;
		CameraComponent(CameraComponent&& other) = delete;
		CameraComponent& operator=(const CameraComponent& other) = delete;
		CameraComponent& operator=(CameraComponent&& other) = delete;

		struct Point2i
		{
			float x;
			float y;
		};

		struct Recti
		{
			Point2i position;
			float width;
			float height;
		};

		virtual void Update() override;

		void SetLevelBoundres(const Recti& levelBoundries);
		void Clamp(Point2i& bottomLeftPos) const;
		void Transform(const Recti& rect) const;
		Point2i Track(const Recti& target) const;
		Recti GetCameraRect(const Recti actorShape) const; 

	private:
		const float m_CameraWidth;
		const float m_CameraHeight;
		Recti m_LevelBoundries; 

		GameObject* m_pGameObject;
	};
}