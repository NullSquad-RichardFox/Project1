#include "pch.h"
#include "SlateRenderer.h"
#include "Camera.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "RenderCommand.h"


SlateRenderer::SlateRenderer()
{
	SlateCamera = std::make_shared<Camera>(1920.f / 1080.f, 1.0f, ECameraMode::Orthographic);
	BoxShader = std::make_shared<Shader>(std::string(
#include "../Assets/Shaders/box.glsl"
	));

	FBufferLayout bufferLayout = {
		{ EShaderDataType::Float3, "aPosition" },
		{ EShaderDataType::Float2, "aTexCoord" },
		{ EShaderDataType::Float4, "aColor" },
		{ EShaderDataType::Float, "aTexID" }
	};

	BufferLayout = std::make_shared<FBufferLayout>(bufferLayout);

	CurrentTextureIndex = 0;
	MaxTextureCount = 32;
}

void SlateRenderer::Initialize()
{
	ASSERT(sRendererInstance == nullptr, "Slate renderer already initialized!");
	sRendererInstance = new SlateRenderer();
}

void SlateRenderer::Shutdown()
{
	delete sRendererInstance;
	sRendererInstance = nullptr;
}

void SlateRenderer::OnUpdate(float deltaTime)
{
	sRendererInstance->SlateCamera->OnUpdate(deltaTime);
}

void SlateRenderer::RenderBox(glm::vec2 position, glm::vec2 size, glm::vec4 color, float zOrder)
{
	position.x = position.x / 540.0f - 1.7777777f;
	position.y = position.y / 540 - 1;
	size /= 540.0f;

	sRendererInstance->RenderBox_Int(position, size, zOrder, color, nullptr);
}

void SlateRenderer::RenderBox(glm::vec2 position, glm::vec2 size, const std::shared_ptr<Texture>& texture, float zOrder)
{
	position.x = position.x / 540.0f - 1.7777777f;
	position.y = position.y / 540 - 1;
	size /= 540.0f;

	sRendererInstance->RenderBox_Int(position, size, zOrder, glm::vec4(1.0f), texture.get());
}

void SlateRenderer::Flush()
{
	sRendererInstance->Flush_Int();
}


void SlateRenderer::RenderBox_Int(glm::vec2 position, glm::vec2 size, float zOrder, glm::vec4 color, Texture* texture)
{
	if (size == glm::vec2(0) || color.w == 0) return;

	for (int32 i = 0; i < 4; i++)
	{
		// Bottom left
		BoxVertices.push_back(position.x);
		BoxVertices.push_back(position.y);
		BoxVertices.push_back(zOrder);
		BoxVertices.push_back(0.0f);
		BoxVertices.push_back(0.0f);
		BoxVertices.push_back(color.x);
		BoxVertices.push_back(color.y);
		BoxVertices.push_back(color.z);
		BoxVertices.push_back(color.w);
		BoxVertices.push_back(texture == nullptr ? -1.0f : (float)CurrentTextureIndex);

		// Bottom right
		BoxVertices.push_back(position.x + size.x);
		BoxVertices.push_back(position.y);
		BoxVertices.push_back(zOrder);
		BoxVertices.push_back(1.0f);
		BoxVertices.push_back(0.0f);
		BoxVertices.push_back(color.x);
		BoxVertices.push_back(color.y);
		BoxVertices.push_back(color.z);
		BoxVertices.push_back(color.w);
		BoxVertices.push_back(texture == nullptr ? -1.0f : (float)CurrentTextureIndex);

		// Top right
		BoxVertices.push_back(position.x + size.x);
		BoxVertices.push_back(position.y + size.y);
		BoxVertices.push_back(zOrder);
		BoxVertices.push_back(1.0f);
		BoxVertices.push_back(1.0f);
		BoxVertices.push_back(color.x);
		BoxVertices.push_back(color.y);
		BoxVertices.push_back(color.z);
		BoxVertices.push_back(color.w);
		BoxVertices.push_back(texture == nullptr ? -1.0f : (float)CurrentTextureIndex);

		// Top left
		BoxVertices.push_back(position.x);
		BoxVertices.push_back(position.y + size.y);
		BoxVertices.push_back(zOrder);
		BoxVertices.push_back(0.0f);
		BoxVertices.push_back(1.0f);
		BoxVertices.push_back(color.x);
		BoxVertices.push_back(color.y);
		BoxVertices.push_back(color.z);
		BoxVertices.push_back(color.w);
		BoxVertices.push_back(texture == nullptr ? -1.0f : (float)CurrentTextureIndex);
	}

	if (texture != nullptr)
	{
		texture->Bind(CurrentTextureIndex);
		CurrentTextureIndex++;

		if (CurrentTextureIndex == MaxTextureCount)
			Flush_Int();
	}
}

void SlateRenderer::Flush_Int()
{
	int32 vertexCount = (uint32)BoxVertices.size() / BufferLayout->GetSize();
	ASSERT((BoxVertices.size() % BufferLayout->GetSize()) == 0, "Box vertex data does not match up to current buffer layout!");

	int32 quadCount = vertexCount / 4;
	ASSERT((vertexCount % 4) == 0, "Not enough vertices to make full quads!");

	std::vector<uint32> indices;
	for (uint32 i = 0; i < quadCount; i++)
	{
		indices.push_back(0 + 4 * i);
		indices.push_back(1 + 4 * i);
		indices.push_back(2 + 4 * i);
		indices.push_back(2 + 4 * i);
		indices.push_back(3 + 4 * i);
		indices.push_back(0 + 4 * i);
	}

	std::shared_ptr<VertexArray> vArray = std::make_shared<VertexArray>();
	std::shared_ptr<VertexBuffer> vBuffer = std::make_shared<VertexBuffer>(BoxVertices.data(), (uint32)sizeof(float) * (uint32)BoxVertices.size());
	std::shared_ptr<IndexBuffer> iBuffer = std::make_shared<IndexBuffer>(indices.data(), (uint32)indices.size());

	vBuffer->SetLayout(*BufferLayout);

	vArray->AddVertexBuffer(vBuffer);
	vArray->SetIndexBuffer(iBuffer);

	const glm::mat4& viewProjMatrix = SlateCamera->GetViewProjectionMatrix();
	BoxShader->Bind();
	BoxShader->SetMat4("uViewProjMat", viewProjMatrix);

	RenderCommand::DrawElements(vArray);

	CurrentTextureIndex = 0;
	BoxVertices.clear();
}
