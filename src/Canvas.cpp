#include <wx/rawbmp.h>
#include "MainFrame.hpp"
#include "Canvas.hpp"
#include "design.hpp"
#include "config.hpp"

Canvas::Canvas(wxWindow* parent):
        wxPanel(parent)
{
    SetBackgroundColour(colors::background_color_2);
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

void drawFractal(const wxRealPoint& start, const wxSize& screen_size, std::vector<std::array<double, 6>> transforms, wxDC& dc, int depth, int maxdepth)
{
    if (depth > maxdepth)
    {
        return;
    }
    int i = 0;
    const wxColor* colors[] = {wxRED, wxYELLOW, wxGREEN, wxBLUE, wxBLACK};
    for (const auto& transformation: transforms)
    {
        double a = transformation[0];
        double b = transformation[1];
        double c = transformation[2];
        double d = transformation[3];
        double t1 = transformation[4] * screen_size.GetX();
        double t2 = transformation[5] * screen_size.GetY();

        double newx = start.x*a + start.y*b + t1;
        double newy = start.x*c + start.y*d + t2;
        wxRealPoint newpoint(newx, newy);
        dc.SetPen(wxPen(*colors[i++]));
        dc.DrawPoint(newpoint);
        drawFractal(newpoint, screen_size, transforms, dc, depth+1, maxdepth);
    }
}

void Canvas::render(wxDC& dc)
{
    dc.Clear();
    int fractals_count = MainFrame::animation.fractals_count;
    if (fractals_count == 0) {return;}

    wxPoint starting_point(GetSize().x/2, GetSize().y/2);
    dc.DrawPoint(starting_point);
    int maxdepth = log(config::kpixels_max) / log(MainFrame::animation.fractals.at(0)->transform_count);

    auto trans1 = MainFrame::animation.fractals.at(0)->transformations;
    auto trans2 = MainFrame::animation.fractals.at(1)->transformations;
    drawFractal(starting_point, GetSize(), trans1, dc, 0, maxdepth);
}
