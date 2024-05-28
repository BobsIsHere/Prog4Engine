#pragma once
#include <memory>

#include "UpdateComponent.h"
#include "Collidable.h"

namespace dae
{
	class GameObject;

	class BoundingBoxComponent final : public UpdateComponent
	{
	public:
		BoundingBoxComponent(GameObject* pGameObject, int width, int height);
		virtual ~BoundingBoxComponent();

		struct Rect
		{
			int x;
			int y;
			int width;
			int height;
		};

		BoundingBoxComponent(const BoundingBoxComponent& other) = delete;
		BoundingBoxComponent(BoundingBoxComponent&& other) = delete;
		BoundingBoxComponent& operator=(const BoundingBoxComponent& other) = delete;
		BoundingBoxComponent& operator=(BoundingBoxComponent&& other) = delete;

		virtual void Update() override;

		dae::Rect GetBoundingBox() const;
		void SetBoundingBox(int width, int height);

	private:
		GameObject* m_pGameObject;
		dae::Rect m_BoundingBox;
	};
}