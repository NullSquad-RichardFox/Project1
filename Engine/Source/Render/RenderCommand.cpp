#include "pch.h"
#include "RenderCommand.h"
#include "VertexArray.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


void RenderCommand::Initialize()
{
	glfwInit();
}

void RenderCommand::Shutdown()
{
	glfwTerminate();
}

void RenderCommand::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderCommand::SetClearColor(glm::vec4 color)
{
	glClearColor(color.x, color.y, color.z, color.w);
}

void RenderCommand::DrawElements(const std::shared_ptr<VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
}
