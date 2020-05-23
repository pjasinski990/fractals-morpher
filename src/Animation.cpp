#include "Animation.hpp"
#include <iostream>

int Fractal::getRandomFunctionIndex() const
{
    return rand() % transform_count;
}

std::vector<wxRealPoint> Fractal::generatePoints(unsigned int points_max, const wxSize& drawing_size) const
{
    std::vector<wxRealPoint> points;
    points.reserve(points_max);
    points[0].x = drawing_size.GetWidth() / 2;
    points[0].y = drawing_size.GetHeight() / 2;
    
    for (size_t i = 1; i < points_max; i++)
    {
        const auto& t= transformations.at(getRandomFunctionIndex());
        double a = t[0];
        double b = t[1];
        double c = t[2];
        double d = t[3];
        double t1 = t[4] * drawing_size.GetWidth();
        double t2 = t[5] * drawing_size.GetHeight();

        double newx = points[i-1].x*a + points[i-1].y*b + t1;
        double newy = points[i-1].x*c + points[i-1].y*d + t2;
        points[i].x = newx;
        points[i].y = newy;
    }
    return points;
}

std::string Animation::toString() const
{
    std::string result = "Animaiton of size " + std::to_string(bitmap_size[0]) 
            + " x " + std::to_string(bitmap_size[1]) + "\n";
    result += "Fractals to be morphed: " + std::to_string(fractals_count) + "\n\n"; 
    for (int i = 0; i < fractals_count; i++)
    {
        result += "Fractal number " + std::to_string(i+1) + "\n";
        result += "Transformations:\n";
        auto ptr = fractals.at(i);
        for (int j = 0; j < ptr->transform_count; j++)
        {
            auto arr = ptr->transformations.at(j);
            result += std::to_string(arr[0]) + " " + std::to_string(arr[1]) 
                    + " " + std::to_string(arr[2]) + " " + std::to_string(arr[3]) 
                    + " " + std::to_string(arr[4]) + " " + std::to_string(arr[5]) + "\n";
        }
        if (i != fractals_count-1)
        {
            result += "Frames for animation to next fractal: " + std::to_string(ptr->frames_for_animation) + "\n\n";
        }
    }
    return result;
}
