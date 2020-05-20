#pragma once
#include <vector>
#include <array>
#include <memory>

struct Fractal
{
    int transform_count;
    std::vector<std::array<double, 6>> transformation; // m transformation arrays for each fractal 
    int frames_for_animation; // frames for transition to next 
    std::shared_ptr<Fractal> next = nullptr;
};

struct Animation
{
    std::array<int, 2> bitmap_size;
    int iter_count;
    bool is_3d;
    std::array<double, 3> observer_pos;
    int fractals_count;
    std::vector<std::shared_ptr<Fractal>> transformations_for_fractal; // n for n fractals, each entry has m transformations
};