#pragma once

#include <fluffy/math/math.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

struct Color
{
    Color() = default;
    Color(float r, float g, float b, float a = 1.f);
    Color(const Vector4f& colors);

    static Color fromInt8(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255);

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;
    static const Color Transparent;

    Vector4f value;
};

bool          operator==(const Color& lhs, const Color& rhs);
bool          operator!=(const Color& lhs, const Color& rhs);
Color         operator+(const Color& lhs, const Color& rhs);
Color         operator-(const Color& lhs, const Color& rhs);
Color         operator*(const Color& lhs, const Color& rhs);
std::ostream& operator<<(std::ostream& os, const Color& color);
}

template<>
struct fmt::formatter<Fluffy::Color>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(const Fluffy::Color& c, FormatContext& ctx)
    {
        return format_to(ctx.out(), "{{{}, {}, {}, {}}}", c.value.r, c.value.g, c.value.b, c.value.a);
    }
};
