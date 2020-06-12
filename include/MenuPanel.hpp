#pragma once

#include <wx/wx.h>
#include "InputPanel.hpp"

class MenuPanel: public wxPanel
{
public:
    MenuPanel(wxWindow* parent);
    ~MenuPanel();
    void fillInputFields() const {m_input_panel->setInputFields();}

private:
    wxButton* m_select_button;
    wxButton* m_generate_button;
    wxTextCtrl* m_info;
    wxString m_directory_for_saving;

    InputPanel* m_input_panel;

    void onSelectButtonClicked(wxCommandEvent& e);
    void onGenerateButtonClicked(wxCommandEvent& e);

};
