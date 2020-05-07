#include "Canvas.hpp"
#include "design.hpp"

Canvas::Canvas(wxWindow* parent):
        wxPanel(parent)
{
    SetBackgroundColour(colors::background_color_2);

}

Canvas::~Canvas() = default;
