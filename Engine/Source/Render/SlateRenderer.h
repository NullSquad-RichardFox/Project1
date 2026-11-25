#pragma once


class Texture;
class Shader;
class Camera;
struct FBufferLayout;

class SlateRenderer
{
public:
	static void Initialize();
	static void Shutdown();

	static void OnUpdate(float deltaTime);

	static void RenderBox(glm::vec2 position, glm::vec2 size, glm::vec4 color, float zOrder = 1.0f);
	static void RenderBox(glm::vec2 position, glm::vec2 size, const std::shared_ptr<Texture>& texture, float zOrder = 1.0f);

	static void Flush();

private:
	SlateRenderer();
	inline static SlateRenderer* sRendererInstance = nullptr;

	void RenderBox_Int(glm::vec2 position, glm::vec2 size, float zOrder, glm::vec4 color, Texture* texture);
	void Flush_Int();

	std::shared_ptr<Shader> BoxShader;
	std::shared_ptr<Camera> SlateCamera;
	std::shared_ptr<FBufferLayout> BufferLayout;

	std::vector<float> BoxVertices;
	uint32 MaxTextureCount;
	uint32 CurrentTextureIndex;
};