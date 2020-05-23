#pragma once

#include <wx/wx.h>
#include "Animation.hpp"

class Canvas: public wxPanel
{
public:
    Canvas(wxWindow* parent);
    ~Canvas();
    void generateLoadedAnimation();

private:
    std::vector<wxPoint> m_points_current;
    std::vector<wxPoint> m_points_transition;
    std::vector<wxPoint> m_points_next;
    void onPaintEvent(wxPaintEvent& e);
    void paintNow();
    void render(wxDC& dc);

    void onGenerateButtonClicked(wxCommandEvent& e);

};
