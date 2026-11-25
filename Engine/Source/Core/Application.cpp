#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "Render/RenderCommand.h"
#include "Utility/Time.h"

#include "Render/SlateRenderer.h"


Application::Application()
{
	MainWindow = nullptr;
}

void Application::Initialize()
{
	RAW_ASSERT(sAppInstance == nullptr);
	sAppInstance = this;

	RenderCommand::Initialize();
	Logger::Initialize();
	Time::Initialize();

	MainWindow = std::make_shared<Window>();
	
	SlateRenderer::Initialize();
}

void Application::Shutdown()
{
	SlateRenderer::Shutdown();
	Time::Shutdown();
	Logger::Shutdown();
	RenderCommand::Shutdown();

	delete sAppInstance;
	sAppInstance = nullptr;
}

void Application::Run()
{
	while (true)
	{
		float deltaTime = Time::OnUpdate();

		RenderCommand::Clear();
		RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));

		SlateRenderer::RenderBox(glm::vec2(200, 200), glm::vec2(10, 50), glm::vec4(1, 1, 0, 0.5f));
		SlateRenderer::Flush();

		MainWindow->OnUpdate(deltaTime);
	}
}