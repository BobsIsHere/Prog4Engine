#pragma once

namespace dae
{
	class IUpdateableObject
	{
	public:
		virtual ~IUpdateableObject() = default;
		virtual void Update() = 0;
	};
}