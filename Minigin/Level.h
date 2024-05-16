#pragma once


namespace dae
{
	class Level
	{
	public:
		Level();
		~Level();

		Level(const Level& other) = delete;
		Level(Level&& other) = delete;
		Level& operator=(const Level& other) = delete;
		Level& operator=(Level&& other) = delete;

	private:

	};
}