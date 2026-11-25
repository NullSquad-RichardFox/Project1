#include "pch.h"
#include "Application.h"


Application::Application()
{
}

void Application::Initialize()
{
	ASSERT(sAppInstance == nullptr);
	sAppInstance = this;

	Logger::Initialize();
}

void Application::Shutdown()
{
	Logger::Shutdown();

	delete sAppInstance;
	sAppInstance = nullptr;
}

void Application::Run()
{
	while (true)
	{
	}
}