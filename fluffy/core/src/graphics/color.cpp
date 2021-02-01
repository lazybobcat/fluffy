#include <fluffy/graphics/color.hpp>

using namespace Fluffy;

const Color Color::Black(0.f, 0.f, 0.f);
const Color Color::White(1.f, 1.f, 1.f);
const Color Color::Red(1.f, 0.f, 0.f);
const Color Color::Green(0.f, 1.f, 0.f);
const Color Color::Blue(0.f, 0.f, 1.f);
const Color Color::Yellow(1.f, 1.f, 0.f);
const Color Color::Magenta(1.f, 0.f, 1.f);
const Color Color::Cyan(0.f, 1.f, 1.f);
const Color Color::Transparent(0.f, 0.f, 0.f, 0.f);

Color::Color(float r, float g, float b, float a)
  : value(r, g, b, a)
{
}

Color::Color(const Vector4f& colors)
  : value(colors)
{
}

Color Color::fromInt8(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
    return Color((float)r / 255.f, (float)g / 255.f, (float)b / 255.f, (float)a / 255.f);
}

bool Fluffy::operator==(const Color& lhs, const Color& rhs)
{
    return lhs.value == rhs.value;
}

bool Fluffy::operator!=(const Color& lhs, const Color& rhs)
{
    return !(lhs == rhs);
}

Color Fluffy::operator+(const Color& lhs, const Color& rhs)
{
    return Color(std::min(lhs.value.r + rhs.value.r, 1.f),
                 std::min(lhs.value.g + rhs.value.g, 1.f),
                 std::min(lhs.value.b + rhs.value.b, 1.f),
                 std::min(lhs.value.a + rhs.value.a, 1.f));
}

Color Fluffy::operator-(const Color& lhs, const Color& rhs)
{
    return Color(std::max(lhs.value.r - rhs.value.r, 0.f),
                 std::max(lhs.value.g - rhs.value.g, 0.f),
                 std::max(lhs.value.b - rhs.value.b, 0.f),
                 std::max(lhs.value.a - rhs.value.a, 0.f));
}

Color Fluffy::operator*(const Color& lhs, const Color& rhs)
{
    return Color(lhs.value.r * rhs.value.r,
                 lhs.value.g * rhs.value.g,
                 lhs.value.b * rhs.value.b,
                 lhs.value.a * rhs.value.a);
}

std::ostream& Fluffy::operator<<(std::ostream& os, const Color& color)
{
    os << "{" << color.value.r << ", " << color.value.g << ", " << color.value.b << ", " << color.value.a << "}";

    return os;
}