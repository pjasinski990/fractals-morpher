#pragma once

#include <wx/wx.h>

class Canvas: public wxPanel
{
public:
    Canvas(wxWindow* parent);
    ~Canvas();

private:
    void onUpdateUI(wxUpdateUIEvent& e);
    void Repaint(wxDC& dc);

};
