#include <iomanip>
#include <algorithm>
#include <wx/rawbmp.h>
#include <wx/dcbuffer.h>
#include "MainFrame.hpp"
#include "ColorGenerator.hpp"
#include "Canvas.hpp"
#include "design.hpp"
#include "config.hpp"

Canvas::Canvas(wxWindow* parent):
        wxPanel(parent)
{
    SetBackgroundColour(colors::canvas_color);
    Bind(wxEVT_PAINT, &Canvas::onPaintEvent, this);
}

Canvas::~Canvas()
{
    Unbind(wxEVT_PAINT, &Canvas::onPaintEvent, this);
}

void Canvas::onPaintEvent(wxPaintEvent& e)
{
    wxPaintDC dc(this);
    render(dc);
    e.Skip();
}

void Canvas::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void Canvas::render(wxDC& dc)
{
}

void Canvas::generateLoadedAnimation(const wxString& dir_path)
{
    const Animation& animation{MainFrame::animation};
    const wxSize& size{MainFrame::animation.bitmap_size};

    for (int i = 0; i < animation.fractals_count-1; i++)
    {
        const Fractal& curr_fractal = animation.fractals.at(i);
        const Fractal& next_fractal = animation.fractals.at(i+1);

        auto points_current = curr_fractal.generatePoints(config::kpixels_max, size);
        auto points_next = next_fractal.generatePoints(config::kpixels_max, size);

        std::vector<ColoredPoint> diffs;
        diffs.reserve(config::kpixels_max);
        for (size_t i = 0; i < config::kpixels_max; i++)
        {
            ColoredPoint point = (points_next[i] - points_current[i]) / curr_fractal.frames_for_animation;
            diffs.emplace_back(std::move(point));
        }

        std::vector<wxColor> colors_vec = ColorGenerator::getColorsVector(curr_fractal.transform_count);

        for (int j = 0; j < curr_fractal.frames_for_animation; j++)
        {
            wxBitmap bmp;
            bmp.Create(size, 32);
            wxClientDC dc(this);
            
            wxMemoryDC mdc(bmp);
            mdc.SetBackground(colors::canvas_color);
            mdc.Clear();

            for (size_t k = 0; k < config::kpixels_max; k++)
            {
                points_current[k] += diffs[k];

                if (k > 0 && points_current[k-1].color_index != points_current[k].color_index)
                {
                    mdc.SetPen(wxPen(colors_vec[points_current[k].color_index]));
                }
                
                wxPoint point(points_current[k].x, points_current[k].y);
                mdc.DrawPoint(point);
            }
            std::stringstream ss;
            ss<< std::setw(4) << std::setfill('0') << j;
            std::string filename = "/frame" + std::to_string(i) + "_" + ss.str() + ".png";
            bmp.SaveFile(dir_path + filename, wxBITMAP_TYPE_PNG);

            int bmp_x_position = (GetSize().GetWidth() - size.GetWidth()) / 2;
            int bmp_y_position = (GetSize().GetHeight() - size.GetHeight()) / 2;
            dc.DrawBitmap(bmp, wxPoint(bmp_x_position, bmp_y_position));
        }
    }
}
// TODO refactor this whole thing