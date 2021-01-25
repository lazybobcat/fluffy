#pragma once

#include <fluffy/math/math.hpp>

namespace Fluffy {

template<typename T>
class Rect
{
public:
    Rect();
    Rect(T left, T top, T width, T height);
    Rect(const glm::vec<2, T>& position, const glm::vec<2, T>& size);

    bool contains(glm::vec<2, T> point) const;
    bool intersects(const Rect<T>& other) const;
    bool intersects(const Rect<T>& other, Rect<T>& intersection) const;

    bool operator==(const Rect& rhs) const;
    bool operator!=(const Rect& rhs) const;

    T left;
    T top;
    T width;
    T height;
};

using IntRect   = Rect<std::int32_t>;
using FloatRect = Rect<float>;
}

template<>
struct fmt::formatter<Fluffy::IntRect>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::IntRect& r, FormatContext& ctx)
    {
        return format_to(ctx.out(), "IntRect{{{}, {}, {}, {}}}", r.left, r.top, r.width, r.height);
    }
};

template<>
struct fmt::formatter<Fluffy::FloatRect>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::FloatRect& r, FormatContext& ctx)
    {
        return format_to(ctx.out(), "IntRect{{{}, {}, {}, {}}}", r.left, r.top, r.width, r.height);
    }
};

#include <fluffy/math/rectangle.inl>
