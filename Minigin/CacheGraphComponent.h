#pragma once
#include <imgui.h>
#include "RenderComponent.h"

namespace dae
{
	class CacheGraphComponent final : public RenderComponent 
	{
	public:
		CacheGraphComponent(GameObject* pGameObject);
		~CacheGraphComponent();

		CacheGraphComponent(const CacheGraphComponent& other) = delete;
		CacheGraphComponent(CacheGraphComponent&& other) = delete;
		CacheGraphComponent& operator=(const CacheGraphComponent& other) = delete;
		CacheGraphComponent& operator=(CacheGraphComponent&& other) = delete;

		virtual void Render() const override;
		virtual void RenderGui() override;

		void RenderEx1();
		void RenderEx2();

		void Exercise1(int benchMarkRuns);
		void Exercise2(int benchMarkRuns);
		void Exercise2Alt(int benchMarkRuns);

		void PlotGraph(std::vector<float> data, const ImU32 color);
		void PlotMultiGraph(std::vector<float> data1, std::vector<float> data2, const ImU32 color1, const ImU32 color2);

	private:
		struct Transform
		{
			float matrix[16] = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
			};
		};

		class GameObject3D
		{
		public:
			Transform transform{};
			int ID{};
		};

		class GameObject3DAlt
		{
		public:
			Transform* transform{};
			int ID{};
		};

		SDL_Window* m_pWindow;

		int m_BenchmarkRunsEx1{ 10 };
		int m_BenchmarkRunsEx2{ 100 };

		std::vector<float> m_Ex1Average;
		std::vector<float> m_Ex2Average;
		std::vector<float> m_Ex2AltAverage;
	};
}

