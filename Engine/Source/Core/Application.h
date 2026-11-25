#pragma once


class Window;

class Application
{
public:
	Application();

	void Initialize();
	void Run();
	void Shutdown();

private:
	inline static Application* sAppInstance = nullptr;

	std::shared_ptr<Window> MainWindow;
};