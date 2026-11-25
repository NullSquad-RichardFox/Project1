#include "pch.h"
#include "Time.h"

#include "GLFW/glfw3.h"


void Time::Initialize()
{
	ASSERT(sTimeInstance == nullptr);
	sTimeInstance = new Time();
	sTimeInstance->TimeLastFrame = (float)glfwGetTime();
}

void Time::Shutdown()
{
	delete sTimeInstance;
	sTimeInstance = nullptr;
}

float Time::OnUpdate_Int()
{
	float currTime = (float)glfwGetTime();
	DeltaTime = currTime - TimeLastFrame;
	TimeLastFrame = currTime;

	return DeltaTime;
}