#pragma once
#include <wx/wx.h>
#include <array>
#include "Fractal.hpp"

struct Animation
{
    wxSize bitmap_size; // Size of generated fractals
    int iter_count; // Number of generated points
    bool is_3d; // Set for 3d fractals
    std::array<double, 3> observer_pos; // Only in 3d, otherwise ignored
    int fractals_count; // Number of fractals that will be morphed
    std::vector<Fractal> fractals;  // Vector of specific fractals

    std::string toString() const;
    std::vector<wxBitmap> generateBitmaps(wxDC& dc, const wxSize& canvas_size) const;
};
