#pragma once
#include <memory>

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		Component(std::weak_ptr<GameObject> pGameObject);
		virtual ~Component();

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Render() const = 0;
		virtual void Update(float deltaTime) = 0;

	protected:
		std::weak_ptr<GameObject> GetGameObject() const { return m_pGameObject; };

	private:
		std::weak_ptr<GameObject> m_pGameObject;
	};
}

