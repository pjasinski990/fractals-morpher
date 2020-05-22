#pragma once

#include <wx/wx.h>

class MainPanel: public wxPanel
{
public:
    MainPanel(wxWindow* parent);
    ~MainPanel();
    void setInfoText(const std::string& text);

private:
    wxPanel* m_canvas;
    wxPanel* m_menu_panel;
    wxTextCtrl* m_info;

};