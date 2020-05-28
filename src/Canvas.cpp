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

void drawFractal(std::vector<wxPoint>& points, std::vector<transformation_t> transforms, const wxSize& screen_size, wxDC& dc)
{
    points[0].x = screen_size.GetWidth()/2;
    points[0].y = screen_size.GetHeight()/2;
    for (size_t i = 1; i < config::kpixels_max; i++)
    {
        int index = rand()%transforms.size();
        const auto& transformation = transforms.at(index);
        double a = transformation[0];
        double b = transformation[1];
        double c = transformation[2];
        double d = transformation[3];
        double t1 = transformation[4] * screen_size.GetX();
        double t2 = transformation[5] * screen_size.GetY();

        double newx = points[i-1].x*a + points[i-1].y*b + t1;
        double newy = points[i-1].x*c + points[i-1].y*d + t2;
        points[i].x = newx;
        points[i].y = newy;
        dc.DrawPoint(wxRealPoint(newx, newy));
    }
}

void Canvas::render(wxDC& dc)
{
}

void Canvas::generateLoadedAnimation(const wxString& dir_path)
{
    const Animation& animation = MainFrame::animation;
    const wxSize size(MainFrame::animation.bitmap_size.first, MainFrame::animation.bitmap_size.second);
    for (int i = 0; i < animation.fractals_count-1; i++)
    {
        const Fractal& curr_fractal = animation.fractals.at(i);
        const Fractal& next_fractal = animation.fractals.at(i+1);
        auto points_current = curr_fractal.generatePoints(config::kpixels_max, size);
        auto points_next = next_fractal.generatePoints(config::kpixels_max, size);
        std::sort(std::begin(points_current), std::end(points_current));
        std::sort(std::begin(points_next), std::end(points_next));

        std::unique_ptr<std::pair<double, double>[]> diffs(new std::pair<double, double>[config::kpixels_max]);
        for (size_t i = 0; i < config::kpixels_max; i++)
        {
            diffs[i].first = static_cast<double>(points_next[i].x - points_current[i].x) / curr_fractal.frames_for_animation;
            diffs[i].second = static_cast<double>(points_next[i].y - points_current[i].y) / curr_fractal.frames_for_animation;
        }

        std::vector<wxColor> colors_vec;
        for (int i = 0; i < curr_fractal.transform_count; i++)
        {
            colors_vec.push_back(ColorGenerator::getNewColor());
        }

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
                points_current[k].x += diffs[k].first;
                points_current[k].y += diffs[k].second;

                mdc.SetPen(wxPen(colors_vec[points_current[k].color_index]));
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