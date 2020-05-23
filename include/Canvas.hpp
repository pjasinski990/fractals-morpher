#pragma once

#include <wx/wx.h>
#include "Animation.hpp"

class Canvas: public wxPanel
{
public:
    Canvas(wxWindow* parent);
    ~Canvas();
    void generateLoadedAnimation(const wxString& dir_path);

private:
    void onPaintEvent(wxPaintEvent& e);
    void paintNow();
    void render(wxDC& dc);

};
