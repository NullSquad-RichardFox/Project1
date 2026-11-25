#include "pch.h"
#include "Application.h"


Application::Application()
{
}

void Application::Initialize()
{
	ASSERT(sAppInstance == nullptr);
	sAppInstance = this;
}

void Application::Shutdown()
{
	delete sAppInstance;
	sAppInstance = nullptr;
}

void Application::Run()
{
	while (true)
	{
	}
}