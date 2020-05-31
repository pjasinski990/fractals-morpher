#include <algorithm>
#include "Fractal.hpp"

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
    std::sort(std::begin(result), std::end(result));
    return result;
}
