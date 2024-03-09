#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <imgui_plot.h>

#include <chrono>
#include <algorithm>

#include "CacheGraphComponent.h"
#include "Renderer.h"

dae::CacheGraphComponent::CacheGraphComponent(GameObject* pGameObject) :
	RenderComponent{ pGameObject }, 
	m_pWindow{}
{
	m_pWindow = Renderer::GetInstance().GetWindow();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_pWindow, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

dae::CacheGraphComponent::~CacheGraphComponent()
{
	ImGui_ImplOpenGL3_Shutdown(); 
	ImGui_ImplSDL2_Shutdown(); 
	ImGui::DestroyContext(); 
}

void dae::CacheGraphComponent::Render() const
{
}

void dae::CacheGraphComponent::RenderGui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	RenderEx1();
	RenderEx2();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void dae::CacheGraphComponent::RenderEx1()
{
	ImGui::Begin("Exercise 1");
	ImGui::InputInt("# samples", &m_BenchmarkRunsEx1);
	if (m_BenchmarkRunsEx1 < 1)
	{
		m_BenchmarkRunsEx1 = 1;
	}
	if (ImGui::Button("Trash the cache"))
	{
		m_Ex1Average.clear(); 
		Exercise1(m_BenchmarkRunsEx1);
	}

	if (m_Ex1Average.size() > 0)
	{
		const ImU32 color{ ImColor(255, 150, 0) }; 
		PlotGraph(m_Ex1Average, color); 
	}

	ImGui::End();
}

void dae::CacheGraphComponent::RenderEx2()
{
	ImGui::Begin("Exercise 2");
	ImGui::InputInt("# samples", &m_BenchmarkRunsEx2);
	if (m_BenchmarkRunsEx2 < 1)
	{
		m_BenchmarkRunsEx2 = 1;
	}

	if (ImGui::Button("Trash the cache with GameObject3D"))
	{
		m_Ex2Average.clear();
		Exercise2(m_BenchmarkRunsEx2);
	}
	if (m_Ex2Average.size() > 0)
	{
		const ImU32 color{ ImColor(0, 255, 150) };
		PlotGraph(m_Ex2Average, color);
	}

	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		m_Ex2AltAverage.clear();
		Exercise2Alt(m_BenchmarkRunsEx2); 
	}
	if (m_Ex2AltAverage.size() > 0)
	{
		const ImU32 color{ ImColor(0, 100, 200) };
		PlotGraph(m_Ex2AltAverage, color);
	}

	if (m_Ex2Average.size() > 0 and m_Ex2AltAverage.size() > 0)
	{
		const ImU32 colorEx2{ ImColor(0, 255, 150) };
		const ImU32 colorEx2Alt{ ImColor(0, 100, 200) };
		PlotMultiGraph(m_Ex2Average, m_Ex2AltAverage, colorEx2, colorEx2Alt);
	}

	ImGui::End(); 
}

void dae::CacheGraphComponent::Exercise1(int benchMarkRuns)
{
	const int arraySize{ 10'000'000 };

	int* buffer{ new int[arraySize] {} };
	std::vector<long long> executationTime{};

	for (size_t stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		for (size_t runIndex = 0; runIndex < benchMarkRuns; ++runIndex) 
		{
			const auto start = std::chrono::high_resolution_clock::now();

			for (size_t idx = 0; idx < arraySize; idx += stepsize)
			{
				buffer[idx] *= 2;
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			executationTime.push_back(total);

		}

		std::sort(executationTime.begin(), executationTime.end());
		executationTime.erase(executationTime.begin());
		executationTime.pop_back();

		float sum{};
		for (long long time : executationTime) 
		{
			sum += time;
		}
		float average{ sum / executationTime.size() };

		m_Ex1Average.push_back(average);

		executationTime.clear();
	}

	delete[] buffer;
	buffer = nullptr;
}

void dae::CacheGraphComponent::Exercise2(int benchMarkRuns)
{
	const int arraySize{ 10'000'000 };

	std::vector<GameObject3D> gameObjects{ arraySize };
	std::vector<long long> executationTime{};

	for (size_t stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		for (size_t runIndex = 0; runIndex < benchMarkRuns; ++runIndex) 
		{
			const auto start = std::chrono::high_resolution_clock::now();
			for (size_t idx = 0; idx < arraySize; idx += stepsize)
			{
				gameObjects[idx].ID *= 2;
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			executationTime.push_back(total);
		}

		std::sort(executationTime.begin(), executationTime.end());
		executationTime.erase(executationTime.begin());
		executationTime.pop_back();

		float sum{};
		for (long long time : executationTime) 
		{ 
			sum += time;
		}
		float average{ sum / executationTime.size() };

		m_Ex2Average.push_back(average);

		executationTime.clear();
	}
}

void dae::CacheGraphComponent::Exercise2Alt(int benchMarkRuns)
{
	const int arraySize{ 10'000'000 };

	std::vector<GameObject3DAlt> gameObjects{ arraySize }; 
	std::vector<long long> executationTime{}; 

	for (size_t stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		for (size_t runIndex = 0; runIndex < benchMarkRuns; ++runIndex)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			for (size_t idx = 0; idx < arraySize; idx += stepsize)
			{
				gameObjects[idx].ID *= 2;
			}
			const auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			executationTime.push_back(total);
		}

		std::sort(executationTime.begin(), executationTime.end());
		executationTime.erase(executationTime.begin());
		executationTime.pop_back();

		float sum{};
		for (long long time : executationTime)
		{
			sum += time;
		}
		float average{ sum / executationTime.size() };

		m_Ex2AltAverage.push_back(average);

		executationTime.clear();
	}
}

void dae::CacheGraphComponent::PlotGraph(std::vector<float> data, const ImU32 color) 
{
	const std::vector<float> stepInfo{ 1,2,4,8,16,32,64,128,256,512,1024 };

	const float min = *std::min_element(begin(data), end(data));
	const float max = *std::max_element(begin(data), end(data));

	ImGui::PlotConfig plotConfig{};
	plotConfig.values.xs = stepInfo.data();
	plotConfig.values.ys = data.data();
	plotConfig.values.count = int(stepInfo.size());
	plotConfig.values.color = color;
	plotConfig.scale.min = min;
	plotConfig.scale.max = max;
	plotConfig.tooltip.show = true;
	plotConfig.tooltip.format = "x=%.2f, y=%.2f";
	plotConfig.grid_x.show = false;
	plotConfig.grid_y.show = true;
	plotConfig.grid_y.size = max / 10.f;
	plotConfig.frame_size = ImVec2(200, 100);
	plotConfig.line_thickness = 2.f;

	ImGui::Plot("plot", plotConfig);
}

void dae::CacheGraphComponent::PlotMultiGraph(std::vector<float> data1, std::vector<float> data2, const ImU32 color1, const ImU32 color2)
{
	//Variables
	const std::vector<float> stepInfo{ 1,2,4,8,16,32,64,128,256,512,1024 };

	const ImU32 colors[2] = { color1, color2 }; 

	const float* dataArray[] = { data1.data(), data2.data() };
	
	//Graph
	ImGui::Text("Combined Graphs: ");
	ImGui::PlotConfig plotConfig{};
	plotConfig.values.xs = stepInfo.data();
	plotConfig.values.ys_list = dataArray; 
	plotConfig.values.ys_count = 2; 
	plotConfig.values.count = int(stepInfo.size());
	plotConfig.values.colors = colors; 
	plotConfig.scale.min = 0.f;
	plotConfig.scale.max = 100'000.f;
	plotConfig.tooltip.show = true;
	plotConfig.tooltip.format = "x=%.2f, y=%.2f";
	plotConfig.grid_x.show = false;
	plotConfig.grid_y.show = true;
	plotConfig.grid_y.size = 10'000.f;
	plotConfig.frame_size = ImVec2(200, 100);
	plotConfig.line_thickness = 2.f; 

	ImGui::Plot("plot", plotConfig);
}
