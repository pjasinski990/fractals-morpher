#pragma once

#include <wx/wx.h>

class MainPanel: public wxPanel
{
public:
    MainPanel(wxWindow* parent);
    ~MainPanel();

private:
    wxPanel* m_canvas;
    wxPanel* m_menu_panel;

};