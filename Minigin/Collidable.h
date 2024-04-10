#pragma once

namespace dae
{
	struct Rect
	{
		int x;
		int y;
		int width;
		int height;
	};

	class Collidable
	{
	public:
		virtual ~Collidable() = default;
		virtual Rect GetBoundingBox() const = 0;
	};
}