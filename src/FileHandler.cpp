#include <fstream>
#include <iostream>
#include "FileHandler.hpp"

Animation FileHandler::loadAnimationFromFile(const char* file_path)
{
    std::ifstream fin(file_path);
    if (!fin.is_open())
    {
        fin.close();
        throw std::ios_base::failure("Error opening file " + std::string(file_path));
    }

    Animation animation;
    fin >> animation.bitmap_size[0] >> animation.bitmap_size[1] >> animation.iter_count >> animation.is_3d;
    fin >> animation.observer_pos[0] >> animation.observer_pos[1] >> animation.observer_pos[2];
    fin >> animation.fractals_count;

    for (int i = 0; i < animation.fractals_count; i++)
    {
        auto ptr = std::make_shared<Fractal>();
        fin >> ptr->transform_count;
        for (int j = 0; j < ptr->transform_count; j++)
        {
            std::array<double, 6> arr;
            fin >> arr[0] >> arr[1] >> arr[2] >> arr[3] >> arr[4] >> arr[5];
            ptr->transformations.push_back(arr);
        }
        if (i != animation.fractals_count-1)  // if not last fractal
        {
            fin >> ptr->frames_for_animation;
        }
        if (i > 0)
        {
            animation.fractals.at(i-1)->next = ptr;
        }
        animation.fractals.push_back(ptr);
    }
    fin.close();
    return std::move(animation);
}

void FileHandler::saveAnimationToFile(const char* file_path, const Animation& animation)
{
    std::ofstream fout(file_path);
    if (!fout.is_open())
    {
        fout.close();
        throw std::ios_base::failure("Error opening file " + std::string(file_path));
    }

    fout << animation.bitmap_size[0] << " " << animation.bitmap_size[1] << " " << animation.iter_count << " " << animation.is_3d << std::endl;
    fout << animation.observer_pos[0] << " " << animation.observer_pos[1] << " " << animation.observer_pos[2] << std::endl;
    fout << animation.fractals_count << std::endl;

    for (int i = 0; i < animation.fractals_count; i++)
    {
        auto ptr = animation.fractals.at(i);
        fout << ptr->transform_count << std::endl;
        for (int j = 0; j < ptr->transform_count; j++)
        {
            auto arr = ptr->transformations.at(j);
            fout << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << " " << arr[4] << " " << arr[5] << std::endl;
        }
        if (i != animation.fractals_count-1)  // if not last fractal
        {
            fout << ptr->frames_for_animation << std::endl;
        }
    }
    fout.close();
}
