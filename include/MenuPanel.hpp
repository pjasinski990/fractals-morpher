#pragma once

#include <wx/wx.h>

class MenuPanel: public wxPanel
{
public:
    MenuPanel(wxWindow* parent);
    ~MenuPanel();

private:
    wxButton* m_select_button;
    wxButton* m_generate_button;
    wxTextCtrl* m_info;
    wxString m_directory_for_saving;

    void onSelectButtonClicked(wxCommandEvent& e);
    void onGenerateButtonClicked(wxCommandEvent& e);

};
