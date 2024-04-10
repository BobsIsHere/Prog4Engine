#pragma once
#include <chrono>
#include "Singleton.h"

namespace dae
{
	class DeltaTime final : public Singleton<DeltaTime>
	{
	public:
		void UpdateDeltaTime();
		float GetDeltaTime() const;

	private:
		friend class Singleton<DeltaTime>;

		DeltaTime() = default;
		~DeltaTime() = default;

		DeltaTime(const DeltaTime& other) = delete; 
		DeltaTime& operator=(const DeltaTime& other) = delete;

		float m_DeltaTime{};
		std::chrono::high_resolution_clock::time_point m_LastTime{ std::chrono::high_resolution_clock::now() }; 
	};
}