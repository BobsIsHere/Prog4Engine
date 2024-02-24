#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		Component();
		virtual ~Component();

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Render() const = 0;
		virtual void Update(float) = 0;

	protected:
		GameObject* m_GameObject;
	};
}

