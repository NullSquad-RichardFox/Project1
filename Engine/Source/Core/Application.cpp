#include "pch.h"
#include "Application.h"
#include "Utility/Time.h"


Application::Application()
{
}

void Application::Initialize()
{
	ASSERT(sAppInstance == nullptr);
	sAppInstance = this;

	Logger::Initialize();
	Time::Initialize();
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
	}
}