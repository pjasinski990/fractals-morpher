#pragma once

struct ColoredPoint
{
    ColoredPoint() = default;
    ColoredPoint(double x, double y, int color = -1): x{x}, y{y}, color_index{color} {}
    ColoredPoint(double x, double y, double z, int color = -1): x{x}, y{y}, z{z}, color_index{color} {}

    bool operator<(const ColoredPoint& o) {return color_index < o.color_index;}
    ColoredPoint& operator+=(const ColoredPoint& o);
    ColoredPoint& operator-=(const ColoredPoint& o);
    ColoredPoint& operator/=(int i);
    ColoredPoint& operator*=(int i);
    friend ColoredPoint operator+(ColoredPoint o1, const ColoredPoint& o2);
    friend ColoredPoint operator-(ColoredPoint o1, const ColoredPoint& o2);
    friend ColoredPoint operator/(ColoredPoint o, int i);
    friend ColoredPoint operator*(ColoredPoint o, int i);

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    int color_index;
};
