#include <fluffy/graphics/color.hpp>

using namespace Fluffy;

const Color Color::Black(0, 0, 0);
const Color Color::White(255, 255, 255);
const Color Color::Red(255, 0, 0);
const Color Color::Green(0, 255, 0);
const Color Color::Blue(0, 0, 255);
const Color Color::Yellow(255, 255, 0);
const Color Color::Magenta(255, 0, 255);
const Color Color::Cyan(0, 255, 255);
const Color Color::Transparent(0, 0, 0, 0);

Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
  : r(r)
  , g(g)
  , b(b)
  , a(a)
{
}

bool Fluffy::operator==(const Color& lhs, const Color& rhs)
{
    return lhs.r == rhs.r &&
           lhs.g == rhs.g &&
           lhs.b == rhs.b &&
           lhs.a == rhs.a;
}

bool Fluffy::operator!=(const Color& lhs, const Color& rhs)
{
    return !(lhs == rhs);
}

Color Fluffy::operator+(const Color& lhs, const Color& rhs)
{
    return Color(std::min(lhs.r + rhs.r, 255),
                 std::min(lhs.g + rhs.g, 255),
                 std::min(lhs.b + rhs.b, 255),
                 std::min(lhs.a + rhs.a, 255));
}

Color Fluffy::operator-(const Color& lhs, const Color& rhs)
{
    return Color(std::max(lhs.r - rhs.r, 0),
                 std::max(lhs.g - rhs.g, 0),
                 std::max(lhs.b - rhs.b, 0),
                 std::max(lhs.a - rhs.a, 0));
}

Color Fluffy::operator*(const Color& lhs, const Color& rhs)
{
    return Color(lhs.r * rhs.r / 255,
                 lhs.g * rhs.g / 255,
                 lhs.b * rhs.b / 255,
                 lhs.a * rhs.a / 255);
}

std::ostream& Fluffy::operator<<(std::ostream& os, const Color& color)
{
    os << "{" << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << ", " << (int)color.a << "}";

    return os;
}