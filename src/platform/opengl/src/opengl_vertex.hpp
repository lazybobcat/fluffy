#pragma once

#include <fluffy/graphics/vertex.hpp>
#include <glad/glad.h>

namespace Fluffy {

class OpenGLVertexBuffer : public VertexBuffer
{
public:
    OpenGLVertexBuffer(void* vertices, std::size_t size);
    ~OpenGLVertexBuffer() override;

    void                setLayout(const BufferLayout& layout) override;
    const BufferLayout& getLayout() const override;

    void setData(void* vertices, std::size_t size, std::size_t offset) override;

    void bind() override;
    void unbind() override;

private:
    std::uint32_t mBufferId;
    BufferLayout  mLayout;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
    OpenGLIndexBuffer(std::uint32_t* indices, std::size_t count);
    ~OpenGLIndexBuffer() override;

    void        bind() override;
    void        unbind() override;
    std::size_t count() const override;

private:
    std::uint32_t mBufferId;
    std::size_t   mCount = 0;
};

class OpenGLVertexArray : public VertexArray
{
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    void bind() override;
    void unbind() override;

    void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
    void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

    [[nodiscard]] const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override;
    [[nodiscard]] const Ref<IndexBuffer>&               getIndexBuffer() const override;

private:
    std::uint32_t                  mArrayId;
    std::vector<Ref<VertexBuffer>> mVertexBuffers;
    Ref<IndexBuffer>               mIndexBuffer;
};
}