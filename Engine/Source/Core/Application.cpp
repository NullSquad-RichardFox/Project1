#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "Utility/Time.h"


Application::Application()
{
	MainWindow = nullptr;
}

void Application::Initialize()
{
	ASSERT(sAppInstance == nullptr);
	sAppInstance = this;

	Logger::Initialize();
	Time::Initialize();

	MainWindow = std::make_shared<Window>();
}

void Application::Shutdown()
{
	Time::Shutdown();
	Logger::Shutdown();

	delete sAppInstance;
	sAppInstance = nullptr;
}

void Application::Run()
{
	while (true)
	{
		float deltaTime = Time::OnUpdate();
		MainWindow->OnUpdate(deltaTime);
	}
}