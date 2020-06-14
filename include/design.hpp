#pragma once

#include <wx/wx.h>

namespace colors 
{
    static const wxColor background_color_1(80, 80, 80);
    static const wxColor background_color_2(150, 150, 150);
    static const wxColor canvas_color(20, 20, 20);
}

namespace design_constants
{
    static const double ksaturation = 1.0;
    static const double kvalue = 0.8;
}

namespace static_text
{
    static const char* bitmap_size_label = "Generated bitmap size (x, y)";
    static const char* points_count_label = "Number of points generated";

    static const char* fractal1_label = "First fractal";
    static const char* fractal2_label = "Second fractal";
    static const char* frames_to_second_label = "Number of frames for transition";
    static const char* transform_count_label = "Number of transformations (max 5)";
    static const char* transforms_label = "Transformations (a, b, c, d, e, f)";
}