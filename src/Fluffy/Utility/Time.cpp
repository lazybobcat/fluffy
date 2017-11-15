//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 14/11/17.
//

#include <Fluffy/Utility/Time.hpp>

using namespace Fluffy::Utility;

Time::Time(std::int64_t microseconds)
  : mMicroseconds(microseconds)
{
}

Time::Time(std::chrono::microseconds microseconds)
  : mMicroseconds(microseconds.count())
{
}

float Time::seconds() const
{
    return mMicroseconds / 1000000.f;
}

std::int32_t Time::milliseconds() const
{
    return static_cast<std::int32_t>(mMicroseconds / 1000);
}

std::int64_t Time::microseconds() const
{
    return mMicroseconds;
}

/**********************************************************************************************************************/

Time Fluffy::Utility::seconds(float sec)
{
    return { static_cast<std::int64_t>(sec * 1000000) };
}

Time Fluffy::Utility::seconds(std::chrono::seconds sec)
{
    return { std::chrono::microseconds(sec) };
}

Time Fluffy::Utility::milliseconds(std::int32_t ms)
{
    return { static_cast<std::int64_t>(ms * 1000) };
}

Time Fluffy::Utility::milliseconds(std::chrono::milliseconds ms)
{
    return { std::chrono::microseconds(ms) };
}

Time Fluffy::Utility::microseconds(std::int64_t us)
{
    return { us };
}

Time Fluffy::Utility::microseconds(std::chrono::microseconds us)
{
    return { std::chrono::microseconds(us) };
}

/**********************************************************************************************************************/

bool Fluffy::Utility::operator==(Time left, Time right)
{
    return left.microseconds() == right.microseconds();
}

bool Fluffy::Utility::operator!=(Time left, Time right)
{
    return left.microseconds() != right.microseconds();
}

bool Fluffy::Utility::operator<(Time left, Time right)
{
    return left.microseconds() < right.microseconds();
}

bool Fluffy::Utility::operator>(Time left, Time right)
{
    return left.microseconds() > right.microseconds();
}

bool Fluffy::Utility::operator<=(Time left, Time right)
{
    return left.microseconds() <= right.microseconds();
}

bool Fluffy::Utility::operator>=(Time left, Time right)
{
    return left.microseconds() >= right.microseconds();
}

Time Fluffy::Utility::operator-(Time right)
{
    return microseconds(-right.microseconds());
}

Time Fluffy::Utility::operator+(Time left, Time right)
{
    return microseconds(left.microseconds() + right.microseconds());
}

Time& Fluffy::Utility::operator+=(Time& left, Time right)
{
    return left = left + right;
}

Time Fluffy::Utility::operator-(Time left, Time right)
{
    return microseconds(left.microseconds() - right.microseconds());
}

Time& Fluffy::Utility::operator-=(Time& left, Time right)
{
    return left = left - right;
}

Time Fluffy::Utility::operator*(Time left, float right)
{
    return seconds(left.seconds() * right);
}

Time Fluffy::Utility::operator*(Time left, std::uint64_t right)
{
    return microseconds(left.microseconds() * right);
}

Time Fluffy::Utility::operator*(float left, Time right)
{
    return right * left;
}

Time Fluffy::Utility::operator*(std::uint64_t left, Time right)
{
    return right * left;
}

Time& Fluffy::Utility::operator*=(Time& left, float right)
{
    return left = left * right;
}

Time& Fluffy::Utility::operator*=(Time& left, std::uint64_t right)
{
    return left = left * right;
}

Time Fluffy::Utility::operator/(Time left, float right)
{
    return seconds(left.seconds() / right);
}

Time Fluffy::Utility::operator/(Time left, std::uint64_t right)
{
    return microseconds(left.microseconds() / right);
}

Time& Fluffy::Utility::operator/=(Time& left, float right)
{
    return left = left / right;
}

Time& Fluffy::Utility::operator/=(Time& left, std::uint64_t right)
{
    return left = left / right;
}

float Fluffy::Utility::operator/(Time left, Time right)
{
    return left.seconds() / right.seconds();
}