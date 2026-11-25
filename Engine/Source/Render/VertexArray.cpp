#include "pch.h"
#include "VertexArray.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &ArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ArrayID);
}

void VertexArray::Bind()
{
	glBindVertexArray(ArrayID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	glBindVertexArray(ArrayID);
	vertexBuffer->Bind();

	ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

	uint32 index = 0;
	for (auto& element : vertexBuffer->GetLayout())
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(
			index,
			Utils::GetShaderDataTypeComponentCount(element.Type),
			Utils::GetShaderDataTypeToOpenGLBaseType(element.Type),
			element.bNormalized ? GL_TRUE : GL_FALSE,
			vertexBuffer->GetLayout().GetStride(),
			(const void*)element.Offset
		);
		index++;
	}

	VertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(ArrayID);
	indexBuffer->Bind();

	IndexBufferPtr = indexBuffer;
}

void VertexArray::LoadVertexData(const std::vector<float>& data)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * data.size(), data.data());
}

void VertexArray::BindAll()
{
	glBindVertexArray(ArrayID);

	for (const auto& buffer : VertexBuffers)
		buffer->Bind();

	IndexBufferPtr->Bind();
}

void VertexArray::UnbindAll()
{
	glBindVertexArray(0);

	for (const auto& buffer : VertexBuffers)
		buffer->Unbind();

	IndexBufferPtr->Unbind();
}