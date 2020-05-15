#pragma once
#include <vector>
#include <array>

struct Transformation
{
    std::vector<std::array<int, 6>> transformation; // m transformation arrays for each fractal 
};

struct TransformParams
{
    std::array<int, 2> bitmap_size;
    int iter_count;
    bool is_3d;
    std::array<int, 3> observer_pos;
    int fractals_count;

    std::vector<int> transformations_for_fractal_count; // n entries for n fractals
    std::vector<int> frames_for_transition; // n-1 entries for n fractals
    std::vector<Transformation> transformations_for_fractal; // n for n fractals, each entry has m transformations

};
