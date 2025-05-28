#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

template <typename T>
class Vec2
{
public:
    T x = 0;
    T y = 0;

    Vec2() = default;

    Vec2(T xin, T yin):
        x(xin), y(yin)
    { }
    
    Vec2(const sf::Vector2<T>& vec):
        x(vec.x), y(vec.y)
    { }

    operator sf::Vector2<T>()
    {
        return sf::Vector2<T>(x, y);
    }

    Vec2 operator + (const Vec2& rhs) const
    {
        // TODO
        return Vec2();
    }

    Vec2 operator - (const Vec2& rhs) const
    {
        // TODO
        return Vec2();
    }


    Vec2 operator * (const T val) const
    {
        // TODO
        return Vec2();
    }


    Vec2 operator / (const T val) const
    {
        // TODO
        return Vec2();
    }

    bool operator == (const Vec2& rhs) const
    {
        // TODO
        return false;
    }

    bool operator != (const Vec2& rhs) const
    {
        // TODO
        return false;
    }

    void operator += (const Vec2& rhs) const
    {
        // TODO
    }

    void operator -= (const Vec2& rhs) const
    {
        // TODO
    }

    void operator *= (const Vec2& rhs) const
    {
        // TODO
    }

    void operator /= (const Vec2& rhs) const
    {
        // TODO
    }

    float dist(const Vec2& rhs) const
    {
        // TODO
        return 0.f;
    }
};

using Vec2f = Vec2<float>;