#pragma once
#include <vector>
#include <array>
#include <wx/wx.h>
#include "ColoredPoint.hpp"
typedef std::array<double, 6> transformation_t;

struct Fractal
{
    int transform_count;    // Number of affine transformations for this fractal
    std::vector<transformation_t> transformations;  // Vector containing each transformations parameters
    int frames_for_animation; // Frames count for animation to next fractal

    int getRandomFunctionIndex() const;
    std::vector<ColoredPoint> generatePoints(unsigned int points_max, const wxSize& drawing_size) const;
};
