#include "pch.h"
#include "Window.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


Window::Window()
{
	WindowData.Title = "";
	WindowData.Width = 1920;
	WindowData.Height = 1080;
	WindowData.bWindowShouldClose = false;
	
	glfwInit();
	WindowHandle = glfwCreateWindow(WindowData.Width, WindowData.Height, WindowData.Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(WindowHandle);

	int32 status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	ASSERT(status);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthFunc(GL_LESS);

	glfwSetWindowUserPointer(WindowHandle, &WindowData);

	glfwSetWindowCloseCallback(WindowHandle, [](GLFWwindow* window)
		{
			FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);
			data->bWindowShouldClose = true;
		});
}

Window::~Window()
{
	glfwDestroyWindow(WindowHandle);
	WindowHandle = nullptr;
}

void Window::OnUpdate(float deltaTime)
{
	if (WindowData.bWindowShouldClose)
	{
		delete this;
		return;
	}
	
	glfwPollEvents();
	glfwSwapBuffers(WindowHandle);
}