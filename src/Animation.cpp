#include "Animation.hpp"
#include <iostream>

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
