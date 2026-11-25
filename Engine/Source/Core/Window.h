#pragma once


struct GLFWwindow;

struct FWindowData
{
	int32 Width;
	int32 Height;
	std::string Title;
	double CursorPosX, CursorPosY;

	bool bWindowShouldClose;
};

class Window
{
public:
	Window();
	~Window();

	void OnUpdate(float deltaTime);

	inline void* GetWindowHandle() const { return (void*)WindowHandle; }
	int32 GetWidth() const { return WindowData.Width; }
	int32 GetHeight() const { return WindowData.Height; }

private:
	// GLFW window context
	GLFWwindow* WindowHandle;
	FWindowData WindowData;
};