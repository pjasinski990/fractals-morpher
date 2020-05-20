#pragma once

#include <wx/wx.h>
#include "Animation.h"

class Canvas: public wxPanel
{
public:
    Canvas(wxWindow* parent);
    ~Canvas();

private:
    void onPaintEvent(wxPaintEvent& e);
    void paintNow();
    void render(wxDC& dc);

};
