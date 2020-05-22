#pragma once

#include <wx/wx.h>

class MenuPanel: public wxPanel
{
public:
    MenuPanel(wxWindow* parent);
    ~MenuPanel();

private:
    wxButton* m_2dbutton;
    wxButton* m_3dbutton;
    wxTextCtrl* m_info;
};