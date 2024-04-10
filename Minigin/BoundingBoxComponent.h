#pragma once
#include <memory>
#include "UpdateComponent.h"

namespace dae
{
	class GameObject;

	class BoundingBoxComponent : public UpdateComponent
	{
	public:
		struct Rect
		{
			int x;
			int y;
			int width;
			int height;
		};

		BoundingBoxComponent(GameObject* pGameObject);
		virtual ~BoundingBoxComponent();

		BoundingBoxComponent(const BoundingBoxComponent& other) = delete;
		BoundingBoxComponent(BoundingBoxComponent&& other) = delete;
		BoundingBoxComponent& operator=(const BoundingBoxComponent& other) = delete;
		BoundingBoxComponent& operator=(BoundingBoxComponent&& other) = delete;

		virtual void Update() override;

		Rect GetBoundingBox() const;
		void SetBoundingBox(int width, int height);

	private:
		GameObject* m_pGameObject;
		Rect m_BoundingBox;

		int m_Width;
		int m_Height;
	};
}