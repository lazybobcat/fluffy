#include <fluffy/graphics/vertex.hpp>

using namespace Fluffy;

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
  : mElements(elements)
{
    calculateOffsetAndStride();
}

void BufferLayout::calculateOffsetAndStride()
{
    std::uint64_t offset = 0;
    mStride              = 0;
    for (auto& element : mElements) {
        element.offset = offset;
        offset += element.size;
        mStride += element.size;
    }
}
