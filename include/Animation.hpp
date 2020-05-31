#pragma once
#include <wx/wx.h>
#include <array>
#include "Fractal.hpp"

struct Animation
{
    wxSize bitmap_size;
    int iter_count;
    bool is_3d;
    std::array<double, 3> observer_pos;
    int fractals_count;
    std::vector<Fractal> fractals;

    std::string toString() const;
};
