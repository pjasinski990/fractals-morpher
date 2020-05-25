#pragma once
#include <wx/wx.h>
#include <vector>
#include <array>
#include <memory>
typedef std::array<double, 6> transformation_t;

struct Fractal
{
    int transform_count;
    std::vector<transformation_t> transformations; // m transformation arrays for each fractal 
    int frames_for_animation; // frames for transition to next 

    int getRandomFunctionIndex() const;
    std::vector<wxRealPoint> generatePoints(unsigned int points_max, const wxSize& drawing_size) const;
};

struct Animation
{
    std::pair<int, int> bitmap_size;
    int iter_count;
    bool is_3d;
    std::array<double, 3> observer_pos;
    int fractals_count;
    std::vector<Fractal> fractals; // n for n fractals, each entry has m transformations

    std::string toString() const;
};
