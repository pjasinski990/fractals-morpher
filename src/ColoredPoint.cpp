#include "ColoredPoint.hpp"

ColoredPoint& ColoredPoint::operator+=(const ColoredPoint& o)
{
    this->x += o.x;
    this->y += o.y;
    this->z += o.z;
    return *this;
}

ColoredPoint& ColoredPoint::operator-=(const ColoredPoint& o)
{
    this->x -= o.x;
    this->y -= o.y;
    this->z -= o.z;
    return *this;
}

ColoredPoint& ColoredPoint::operator/=(int i)
{
    this->x /= i;
    this->y /= i;
    this->z /= i;
    return *this;
}

ColoredPoint& ColoredPoint::operator*=(int i)
{
    this->x *= i;
    this->y *= i;
    this->z *= i;
    return *this;
}

ColoredPoint operator+(ColoredPoint o1, const ColoredPoint& o2)
{
    o1 += o2;
    return o1;
}

ColoredPoint operator-(ColoredPoint o1, const ColoredPoint& o2)
{
    o1 -= o2;
    return o1;
}

ColoredPoint operator/(ColoredPoint o, int i)
{
    o /= i;
    return o;
}

ColoredPoint operator*(ColoredPoint o, int i)
{
    o *= i;
    return o;
}
