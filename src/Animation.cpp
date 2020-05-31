#include "Animation.hpp"
#include <iostream>

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

int Fractal::getRandomFunctionIndex() const
{
    return rand() % transform_count;
}

std::vector<ColoredPoint> Fractal::generatePoints(unsigned int points_max, const wxSize& drawing_size) const
{
    std::vector<ColoredPoint> result;
    result.reserve(points_max);
    
    ColoredPoint last_point(drawing_size.GetWidth() / 2, drawing_size.GetHeight() / 2, 0);
    result.emplace_back(last_point);
    for (size_t i = 1; i < points_max; i++)
    {
        int rand_index = getRandomFunctionIndex();
        const auto& t = transformations.at(rand_index);
        double a = t[0];
        double b = t[1];
        double c = t[2];
        double d = t[3];
        double t1 = t[4] * drawing_size.GetWidth();
        double t2 = t[5] * drawing_size.GetHeight();

        last_point.x = last_point.x*a + last_point.y*b + t1;
        last_point.y = last_point.x*c + last_point.y*d + t2;
        last_point.color_index = rand_index;
        result.emplace_back(last_point);
    }
    return result;
}

std::string Animation::toString() const
{
    std::string result = "Animaiton of size " + std::to_string(bitmap_size.first) 
            + " x " + std::to_string(bitmap_size.second) + "\n";
    result += "Fractals to be morphed: " + std::to_string(fractals_count) + "\n\n"; 
    for (int i = 0; i < fractals_count; i++)
    {
        result += "Fractal number " + std::to_string(i+1) + "\n";
        result += "Transformations:\n";
        Fractal f = fractals[i];
        for (int j = 0; j < f.transform_count; j++)
        {
            auto arr = f.transformations.at(j);
            result += std::to_string(arr[0]) + " " + std::to_string(arr[1]) 
                    + " " + std::to_string(arr[2]) + " " + std::to_string(arr[3]) 
                    + " " + std::to_string(arr[4]) + " " + std::to_string(arr[5]) + "\n";
        }
        if (i != fractals_count-1)
        {
            result += "Frames for animation to next fractal: " + std::to_string(f.frames_for_animation) + "\n\n";
        }
    }
    return result;
}
