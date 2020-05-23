#pragma once

#include <wx/wx.h>

class MenuPanel: public wxPanel
{
public:
    MenuPanel(wxWindow* parent);
    ~MenuPanel();

private:
    wxButton* m_generate_button;
    wxTextCtrl* m_info;

    void onGenerateButtonClicked(wxCommandEvent& e);

};
