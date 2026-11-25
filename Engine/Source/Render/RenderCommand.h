#pragma once


class VertexArray;

class RenderCommand
{
public:
	static void Initialize();
	static void Shutdown();
	static void Clear();
	static void SetClearColor(glm::vec4 color);
	static void DrawElements(const std::shared_ptr<VertexArray>& vertexArray);
};