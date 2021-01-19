#pragma once

#include <fluffy/assert.hpp>
#include <fluffy/graphics/color.hpp>
#include <fluffy/graphics/shader.hpp>
#include <fluffy/math/math.hpp>

namespace Fluffy {

inline std::uint32_t ShaderDataTypeSize(ShaderDataType type)
{
    switch (type) {
        case ShaderDataType::Int:
            return sizeof(std::int32_t);
        case ShaderDataType::Float:
            return sizeof(float);
        case ShaderDataType::Bool:
            return sizeof(bool);
        case ShaderDataType::Vector2f:
            return 2 * sizeof(float);
        case ShaderDataType::Vector3f:
            return 3 * sizeof(float);
        case ShaderDataType::Vector4f:
            return 4 * sizeof(float);
        case ShaderDataType::Vector2i:
            return 2 * sizeof(std::int32_t);
        case ShaderDataType::Vector3i:
            return 3 * sizeof(std::int32_t);
        case ShaderDataType::Vector4i:
            return 4 * sizeof(std::int32_t);
        case ShaderDataType::Vector2u:
            return 2 * sizeof(std::uint32_t);
        case ShaderDataType::Vector3u:
            return 3 * sizeof(std::uint32_t);
        case ShaderDataType::Vector4u:
            return 4 * sizeof(std::uint32_t);
        case ShaderDataType::None:
        default:
            FLUFFY_ASSERT(false, "Unknown ShaderDataType");
            break;
    }

    return 0;
}



struct BufferElement
{
    String         name;
    ShaderDataType type;
    std::uint32_t  size{};
    std::uint64_t  offset{};
    bool           normalized{};

    BufferElement() = default;
    BufferElement(ShaderDataType type, const String&& name, bool normalized = false)
      : name(name)
      , type(type)
      , size(ShaderDataTypeSize(type))
      , offset(0)
      , normalized(normalized)
    {}

    [[nodiscard]] std::uint32_t getComponentCount() const
    {
        switch (type) {
            case ShaderDataType::Int:
                return 1;
            case ShaderDataType::Float:
                return 1;
            case ShaderDataType::Bool:
                return 1;
            case ShaderDataType::Vector2f:
                return 2;
            case ShaderDataType::Vector3f:
                return 3;
            case ShaderDataType::Vector4f:
                return 4;
            case ShaderDataType::Vector2i:
                return 2;
            case ShaderDataType::Vector3i:
                return 3;
            case ShaderDataType::Vector4i:
                return 4;
            case ShaderDataType::Vector2u:
                return 2;
            case ShaderDataType::Vector3u:
                return 3;
            case ShaderDataType::Vector4u:
                return 4;
            case ShaderDataType::None:
                FLUFFY_ASSERT(false, "Unknown ShaderDataType");
                return 0;
        }

        return 0;
    }
};

class BufferLayout
{
public:
    BufferLayout() = default;
    BufferLayout(const std::initializer_list<BufferElement>& elements);

    [[nodiscard]] inline const std::vector<BufferElement>&   getElements() const { return mElements; }
    [[nodiscard]] inline std::uint32_t                       getStride() const { return mStride; }
    std::vector<BufferElement>::iterator                     begin() { return mElements.begin(); }
    std::vector<BufferElement>::iterator                     end() { return mElements.end(); }
    [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
    [[nodiscard]] std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }

private:
    void calculateOffsetAndStride();

private:
    std::vector<BufferElement> mElements;
    std::uint32_t              mStride = 0;
};

class VertexBuffer
{
public:
    virtual ~VertexBuffer() = default;

    static Ref<VertexBuffer> create(std::size_t size);
    static Ref<VertexBuffer> create(void* vertices, std::size_t size);

    virtual void                setLayout(const BufferLayout& layout) = 0;
    virtual const BufferLayout& getLayout() const                     = 0;

    virtual void setData(void* data, std::size_t size) = 0;

    virtual void bind()   = 0;
    virtual void unbind() = 0;

protected:
    VertexBuffer() = default;
};

class IndexBuffer
{
public:
    virtual ~IndexBuffer() = default;

    static Ref<IndexBuffer> create(std::uint32_t* indices, std::size_t count);

    virtual std::size_t count() const = 0;

    virtual void bind()   = 0;
    virtual void unbind() = 0;

protected:
    IndexBuffer() = default;
};

class VertexArray
{
public:
    virtual ~VertexArray() = default;

    static Ref<VertexArray> create();

    virtual void bind()   = 0;
    virtual void unbind() = 0;

    virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)    = 0;

    [[nodiscard]] virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
    [[nodiscard]] virtual const Ref<IndexBuffer>&               getIndexBuffer() const   = 0;

protected:
    VertexArray() = default;
};

}
