#include <wx/rawbmp.h>
#include "Canvas.hpp"
#include "design.hpp"

Canvas::Canvas(wxWindow* parent):
        wxPanel(parent)
{
    SetBackgroundColour(colors::background_color_2);
    Bind(wxEVT_UPDATE_UI, &Canvas::onUpdateUI, this);
}

Canvas::~Canvas()
{
    Unbind(wxEVT_UPDATE_UI, &Canvas::onUpdateUI, this);
}

void Canvas::onUpdateUI(wxUpdateUIEvent& e)
{
    wxClientDC dc(this);
    dc.Clear();
    Repaint(dc);
    e.Skip();
}

void Canvas::Repaint(wxDC& dc)
{
    wxBitmap bmp(this->GetSize().GetWidth(), this->GetSize().GetHeight(), 24);
    wxNativePixelData pixels(bmp);

    wxNativePixelData::Iterator p(pixels);
    p.Offset(pixels, 10, 10);
    for (size_t i = 0; i < 50; i++)
    {
        wxNativePixelData::Iterator row_start = p;
        for (size_t j = 0; j < 50; ++j, ++p)
        {
            p.Red() = 255;
            p.Green() = 0;
            p.Blue() = 0;
        }
        p = row_start;
        p.OffsetY(pixels, 1);
    }
    

    dc.DrawBitmap(bmp, 0, 0, true);
}