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

void drawFractal(const wxRealPoint& start, std::vector<std::array<double, 6>> transforms, wxDC& dc, int depth)
{
    if (depth > config::kdepth_max)
    {
        return;
    }
    
    for (const auto& transformation: transforms)
    {
        double a = transformation[0];
        double b = transformation[1];
        double c = transformation[2];
        double d = transformation[3];
        double t1 = transformation[4];
        double t2 = transformation[5];

        double newx = start.x*a + start.y*b + t1;
        double newy = start.x*c + start.y*d + t2;
        wxRealPoint newpoint(newx, newy);
        dc.DrawPoint(newpoint);
        drawFractal(newpoint, transforms, dc, depth+1);
        std::cout << depth << std::endl;;
    }
}

void Canvas::render(wxDC& dc)
{
    dc.Clear();
    if (MainFrame::animation.fractals_count == 0) {return;}

    wxPoint starting_point(GetSize().x/2, GetSize().y/2);
    dc.DrawPoint(starting_point);
    drawFractal(starting_point, MainFrame::animation.fractals.at(0)->transformations, dc, 0);
    
}
