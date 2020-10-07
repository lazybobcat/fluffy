#pragma once

#include <fluffy/pch.hpp>

namespace Fluffy {

struct Color
{
    Color() = default;
    Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255);

    void getFloatValues(float* r, float* g, float* b, float* a) const;

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;
    static const Color Transparent;

    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
    std::uint8_t a = 255;
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
        return format_to(ctx.out(), "{{{}, {}, {}, {}}}", c.r, c.g, c.b, c.a);
    }
};
