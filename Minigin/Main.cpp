#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& resourceManager = dae::ResourceManager::GetInstance();

	//BACKGROUND
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(go));
	go->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("background.tga"));
	scene.Add(go);

	//BACKGROUND LOGO
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(go));
	go->GetComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("logo.tga"));
	go->SetPosition(216, 180);
	scene.Add(go);

	//BACKRGOUND TEXT
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::GameObject>();
	to->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(to));
	to->AddComponent<dae::TextComponent>(std::make_shared<dae::TextComponent>(to, font));
	to->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	to->SetPosition(100,30);
	scene.Add(to);

	//FPS COUNTER
	to = std::make_shared<dae::GameObject>(); 
	to->AddComponent<dae::TextureComponent>(std::make_shared<dae::TextureComponent>(to));
	to->AddComponent<dae::TextComponent>(std::make_shared<dae::TextComponent>(to, font));
	to->AddComponent<dae::FPSComponent>(std::make_shared<dae::FPSComponent>(to));
	scene.Add(to);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}