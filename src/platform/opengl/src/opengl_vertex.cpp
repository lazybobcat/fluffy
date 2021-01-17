#include "opengl_vertex.hpp"
#include "opengl.hpp"
#include <fluffy/profiling/profiler.hpp>

using namespace Fluffy;

GLenum getOpenGLType(ShaderDataType type)
{
    switch (type) {
        case ShaderDataType::Bool:
            return GL_BOOL;
        case ShaderDataType::Transform:
        case ShaderDataType::Float:
        case ShaderDataType::Vector2f:
        case ShaderDataType::Vector3f:
        case ShaderDataType::Vector4f:
            return GL_FLOAT;
        case ShaderDataType::Int:
        case ShaderDataType::Vector2i:
        case ShaderDataType::Vector3i:
        case ShaderDataType::Vector4i:
            return GL_INT;
        case ShaderDataType::Vector2u:
        case ShaderDataType::Vector3u:
        case ShaderDataType::Vector4u:
            return GL_UNSIGNED_INT;
        case ShaderDataType::None:
            FLUFFY_ASSERT(false, "Unknown ShaderDataType");
            return 0;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Ref<VertexBuffer> VertexBuffer::create(void* data, std::size_t size)
{
    return Fluffy::Ref<VertexBuffer>(new OpenGLVertexBuffer(data, size));
}

Ref<IndexBuffer> IndexBuffer::create(std::uint32_t* indices, std::size_t count)
{
    return Fluffy::Ref<IndexBuffer>(new OpenGLIndexBuffer(indices, count));
}

Ref<VertexArray> VertexArray::create()
{
    return Fluffy::Ref<VertexArray>(new OpenGLVertexArray());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices, std::size_t size)
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glGenBuffers(1, &mBufferId));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, mBufferId));
    GlCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &mBufferId);
}

void OpenGLVertexBuffer::setLayout(const BufferLayout& layout)
{
    mLayout = layout;
}

const BufferLayout& OpenGLVertexBuffer::getLayout() const
{
    return mLayout;
}

void OpenGLVertexBuffer::setData(void* vertices, std::size_t size)
{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, mBufferId));
    GlCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

void OpenGLVertexBuffer::bind()
{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, mBufferId));
}

void OpenGLVertexBuffer::unbind()
{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OpenGLIndexBuffer::OpenGLIndexBuffer(std::uint32_t* indices, std::size_t count)
  : mCount(count)
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glGenBuffers(1, &mBufferId));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferId));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(std::uint32_t), indices, GL_STATIC_DRAW));
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &mBufferId);
}

void OpenGLIndexBuffer::bind()
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferId));
}

void OpenGLIndexBuffer::unbind()
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

std::size_t OpenGLIndexBuffer::count() const
{
    return mCount;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OpenGLVertexArray::OpenGLVertexArray()
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glGenVertexArrays(1, &mArrayId));
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    GlCall(glDeleteVertexArrays(1, &mArrayId));
}

void OpenGLVertexArray::bind()
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glBindVertexArray(mArrayId));
}

void OpenGLVertexArray::unbind()
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glBindVertexArray(0));
}

void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
    FLUFFY_PROFILE_FUNCTION();

    FLUFFY_ASSERT(!vertexBuffer->getLayout().getElements().empty(), "VertexBuffer has no layout associated!");

    GlCall(glBindVertexArray(mArrayId));
    vertexBuffer->bind();
    std::uint32_t index  = 0;
    const auto&   layout = vertexBuffer->getLayout();
    for (const auto& element : layout) {
        GlCall(glEnableVertexAttribArray(index));
        GlCall(glVertexAttribPointer(index, element.getComponentCount(), getOpenGLType(element.type), element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)(element.offset)));
        ++index;
    }

    mVertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
    FLUFFY_PROFILE_FUNCTION();

    GlCall(glBindVertexArray(mArrayId));
    indexBuffer->bind();

    mIndexBuffer = indexBuffer;
}

const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::getVertexBuffers() const
{
    return mVertexBuffers;
}

const Ref<IndexBuffer>& OpenGLVertexArray::getIndexBuffer() const
{
    return mIndexBuffer;
}
