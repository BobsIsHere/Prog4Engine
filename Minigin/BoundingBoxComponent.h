#pragma once
#include <memory>

#include "UpdateComponent.h"

namespace dae
{
	class GameObject;

	class BoundingBoxComponent final : public UpdateComponent
	{
	public:
		BoundingBoxComponent(GameObject* pGameObject, float width, float height);
		virtual ~BoundingBoxComponent();

		struct Rect
		{
			float x;
			float y;
			float width;
			float height;
		};

		BoundingBoxComponent(const BoundingBoxComponent& other) = delete;
		BoundingBoxComponent(BoundingBoxComponent&& other) = delete;
		BoundingBoxComponent& operator=(const BoundingBoxComponent& other) = delete;
		BoundingBoxComponent& operator=(BoundingBoxComponent&& other) = delete;

		virtual void Update() override;

		Rect GetBoundingBox() const;
		void SetBoundingBox(float width, float height);

	private:
		GameObject* m_pGameObject;
		Rect m_BoundingBox;
	};
}