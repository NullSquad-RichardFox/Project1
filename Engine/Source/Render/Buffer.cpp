#include "pch.h"
#include "Buffer.h"

#include "Glad/glad.h"
#include "GLFW/glfw3.h"


uint32 Utils::GetShaderDataTypeSize(EShaderDataType type)
{
	switch (type)
	{
	case EShaderDataType::None:		return 0;
	case EShaderDataType::Float:		return 4;
	case EShaderDataType::Float2:	return 8;
	case EShaderDataType::Float3:	return 12;
	case EShaderDataType::Float4:	return 16;
	case EShaderDataType::Mat3:		return 36;
	case EShaderDataType::Mat4:		return 64;
	case EShaderDataType::int32:		return 4;
	case EShaderDataType::Int2:		return 8;
	case EShaderDataType::Int3:		return 12;
	case EShaderDataType::Int4:		return 16;
	case EShaderDataType::Bool:		return 1;
	}

	ASSERT(false, "Unknown EShaderDataType");
	return 0;
}

uint32 Utils::GetShaderDataTypeComponentCount(EShaderDataType type)
{
	switch (type)
	{
	case EShaderDataType::None:		return 0;
	case EShaderDataType::Float:		return 1;
	case EShaderDataType::Float2:	return 2;
	case EShaderDataType::Float3:	return 3;
	case EShaderDataType::Float4:	return 4;
	case EShaderDataType::Mat3:		return 9;
	case EShaderDataType::Mat4:		return 16;
	case EShaderDataType::int32:		return 1;
	case EShaderDataType::Int2:		return 2;
	case EShaderDataType::Int3:		return 3;
	case EShaderDataType::Int4:		return 4;
	case EShaderDataType::Bool:		return 1;
	}

	ASSERT(false, "Unknown EShaderDataType");
	return 0;
}

GLenum Utils::GetShaderDataTypeToOpenGLBaseType(EShaderDataType type)
{
	switch (type)
	{
	case EShaderDataType::None:		return GL_FALSE;

	case EShaderDataType::Float:
	case EShaderDataType::Float2:
	case EShaderDataType::Float3:
	case EShaderDataType::Float4:
	case EShaderDataType::Mat3:
	case EShaderDataType::Mat4:		return GL_FLOAT;

	case EShaderDataType::int32:
	case EShaderDataType::Int2:
	case EShaderDataType::Int3:
	case EShaderDataType::Int4:      return GL_INT;

	case EShaderDataType::Bool:		return GL_INT;
	}

	ASSERT(false, "Unknown EShaderDataType");
	return 0;
}

VertexBuffer::VertexBuffer(uint32 size)
{
	glCreateBuffers(1, &BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(float* vertices, uint32 size)
{
	glCreateBuffers(1, &BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &BufferID);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//------- Index Buffer -------

IndexBuffer::IndexBuffer(uint32* indices, uint32 count)
	:Count(count)
{
	glCreateBuffers(1, &BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &BufferID);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}