#pragma once
#include <vector>
#include <wx/wx.h>
#include "ColoredPoint.hpp"
typedef std::array<double, 6> transformation_t;

struct Fractal
{
    int transform_count;
    std::vector<transformation_t> transformations;
    int frames_for_animation;

    // virtual void drawOnDC(wxDC& dc, const std::vector<ColoredPoint>& diffs);

    int getRandomFunctionIndex() const;
    std::vector<ColoredPoint> generatePoints(unsigned int points_max, const wxSize& drawing_size) const;
};