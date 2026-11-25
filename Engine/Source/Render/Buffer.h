#pragma once


typedef uint32 GLenum;

enum class EShaderDataType
{
		None,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		int32,
		Int2,
		Int3,
		Int4,
		Bool
};

class Utils
{
public:
	static uint32 GetShaderDataTypeSize(EShaderDataType type);
	static uint32 GetShaderDataTypeComponentCount(EShaderDataType type);
	static GLenum GetShaderDataTypeToOpenGLBaseType(EShaderDataType type);
};

struct FBufferElement
{
	std::string Name;
	EShaderDataType Type;
	uint32 Size;
	uint32 Offset;
	bool bNormalized;

	FBufferElement(EShaderDataType type, const std::string& name, bool bNormalized = false)
		:Name(name), Type(type), Size(Utils::GetShaderDataTypeSize(type)), Offset(0), bNormalized(bNormalized) {}
};

struct FBufferLayout
{
public:
	FBufferLayout() :Elements({}), Stride(0), Size(0) {}
	FBufferLayout(const std::initializer_list<FBufferElement>& elements)
		:Elements(elements), Stride(0), Size(0)
	{
		CalculateOffsetAndStride();
	}

	inline const std::vector<FBufferElement>& GetElements() const { return Elements; }
	inline const uint32 GetStride() const { return Stride; }
	inline const uint32 GetSize() const { return Size; }

	std::vector<FBufferElement>::iterator begin() { return Elements.begin(); }
	std::vector<FBufferElement>::iterator end() { return Elements.end(); }
	std::vector<FBufferElement>::const_iterator begin() const { return Elements.begin(); }
	std::vector<FBufferElement>::const_iterator end() const { return Elements.end(); }

private:
	void CalculateOffsetAndStride()
	{
		uint32 offset = 0;
		for (auto& element : Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			Stride += element.Size;

			Size += Utils::GetShaderDataTypeComponentCount(element.Type);
		}
	}

	std::vector<FBufferElement> Elements;
	uint32 Stride;
	uint32 Size;
};

class VertexBuffer
{
public:
	VertexBuffer(uint32 size);
	VertexBuffer(float* vertices, uint32 size);
	~VertexBuffer();

	void Bind();
	void Unbind();

	void SetLayout(const FBufferLayout& layout) { Layout = layout; };
	const FBufferLayout& GetLayout() const { return Layout; };
private:
	FBufferLayout Layout;
	uint32 BufferID;
};

class IndexBuffer
{
public:
	IndexBuffer(uint32* indices, uint32 count);
	~IndexBuffer();

	void Bind();
	void Unbind();

	uint32 GetCount() const { return Count; };
private:
	uint32 BufferID;
	uint32 Count;
};