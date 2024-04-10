#pragma once
#include <memory>

#include "UpdateComponent.h"
#include "Collidable.h"

namespace dae
{
	class GameObject;

	class BoundingBox : public UpdateComponent, public Collidable 
	{
	public:
		BoundingBox(GameObject* pGameObject);
		virtual ~BoundingBox();

		BoundingBox(const BoundingBox& other) = delete;
		BoundingBox(BoundingBox&& other) = delete;
		BoundingBox& operator=(const BoundingBox& other) = delete;
		BoundingBox& operator=(BoundingBox&& other) = delete;

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