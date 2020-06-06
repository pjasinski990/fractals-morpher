#include <algorithm>
#include <iostream>
#include <iomanip>
#include "Animation.hpp"
#include "ColorGenerator.hpp"
#include "design.hpp"

std::string Animation::toString() const
{
    std::string result = is_3d ? "3D" : "2D";
    result += " animaiton of size " + std::to_string(bitmap_size.GetWidth()) 
            + " x " + std::to_string(bitmap_size.GetHeight()) + "\n";
    result += "Fractals to be morphed: " + std::to_string(fractals_count) + "\n\n"; 
    for (int i = 0; i < fractals_count; i++)
    {
        result += "Fractal number " + std::to_string(i+1) + "\n";
        result += "Transformations:\n";
        Fractal f = fractals[i];
        for (int j = 0; j < f.transform_count; j++)
        {
            auto arr = f.transformations.at(j);
            result += std::to_string(arr[0]) + " " + std::to_string(arr[1]) 
                    + " " + std::to_string(arr[2]) + " " + std::to_string(arr[3]) 
                    + " " + std::to_string(arr[4]) + " " + std::to_string(arr[5]) + "\n";
        }
        if (i != fractals_count-1)
        {
            result += "Frames for animation to next fractal: " + std::to_string(f.frames_for_animation) + "\n\n";
        }
    }
    return result;
}

std::vector<wxBitmap> Animation::generateBitmaps(wxDC& dc, const wxSize& canvas_size) const
{
    std::vector<wxBitmap> result;
    if (is_3d) 
    {
        throw std::runtime_error("3D animations not supported yet");
    }
    
    for (int i = 0; i < fractals_count-1; i++)
    {
        const Fractal& curr_fractal = fractals.at(i);
        const Fractal& next_fractal = fractals.at(i+1);
        auto points_current = curr_fractal.generatePoints(iter_count, bitmap_size);
        auto points_next = next_fractal.generatePoints(iter_count, bitmap_size);

        result.reserve(result.size() + curr_fractal.frames_for_animation);

        std::vector<ColoredPoint> diffs;
        diffs.reserve(iter_count);
        for (size_t i = 0; i < iter_count; i++)
        {
            ColoredPoint point = (points_next[i] - points_current[i]) / curr_fractal.frames_for_animation;
            diffs.emplace_back(point);
        }

        std::vector<wxColor> colors_vec = ColorGenerator::getColorsVector(curr_fractal.transform_count);

        for (int j = 0; j <= curr_fractal.frames_for_animation; j++)
        {
            wxBitmap bmp;
            bmp.Create(bitmap_size, 32);
            wxMemoryDC mdc(bmp);

            mdc.SetBackground(colors::canvas_color);
            mdc.Clear();

            for (size_t k = 0; k < iter_count; k++)
            {
                wxPoint point(points_current[k].x, points_current[k].y);
                mdc.DrawPoint(point);

                points_current[k] += diffs[k];
                if (k > 0 && points_current[k-1].color_index != points_current[k].color_index)
                {
                    mdc.SetPen(wxPen(colors_vec[points_current[k].color_index]));
                }
            }

            wxImage img(bmp.ConvertToImage());
            img.Rescale(canvas_size.GetWidth(), canvas_size.GetHeight());
            dc.DrawBitmap(img, wxPoint(0, 0));

            result.emplace_back(bmp);
        }
    }
    return result;
}