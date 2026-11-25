#pragma once

#include "Buffer.h"


class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind();
	void Unbind();
	void BindAll();
	void UnbindAll();

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
	void LoadVertexData(const std::vector<float>& data);
	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() { return IndexBufferPtr; }

private:
	uint32 ArrayID;
	std::vector<std::shared_ptr<VertexBuffer>> VertexBuffers;
	std::shared_ptr<IndexBuffer> IndexBufferPtr;
};