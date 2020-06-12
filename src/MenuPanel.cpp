#include "MenuPanel.hpp"
#include "MainFrame.hpp"
#include "Canvas.hpp"
#include "design.hpp"

MenuPanel::MenuPanel(wxWindow* parent):
        wxPanel(parent),
        m_select_button{new wxButton(this, wxID_ANY, wxT("Select directory for saving"))},
        m_generate_button{new wxButton(this, wxID_ANY, wxT("Generate animation"))},
        m_input_panel{new InputPanel(this)}
{
    SetBackgroundColour(colors::background_color_2);

    wxBoxSizer* sizer_main = new wxBoxSizer(wxVERTICAL);
    sizer_main->Add(m_select_button, 0, wxALL | wxCENTER, 5);
    sizer_main->Add(m_generate_button, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxCENTER, 5);

    sizer_main->Add(m_input_panel, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxCENTER, 5);

    SetSizerAndFit(sizer_main);

    m_select_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MenuPanel::onSelectButtonClicked, this);
    m_generate_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MenuPanel::onGenerateButtonClicked, this);
}

MenuPanel::~MenuPanel()
{
    m_generate_button->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &MenuPanel::onGenerateButtonClicked, this);
}

void MenuPanel::onSelectButtonClicked(wxCommandEvent& e)
{
    wxDirDialog dialog(this, wxT("Select directory for saving"), wxGetCwd(), wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dialog.ShowModal() == wxID_CANCEL) {return;}

    m_directory_for_saving = dialog.GetPath();
}

void MenuPanel::onGenerateButtonClicked(wxCommandEvent& e)
{
    if (MainFrame::animation.fractals_count == 0)
    {
        wxMessageDialog(this, wxT("No fractal currently loaded."), wxT("Error"), wxICON_ERROR | wxOK).ShowModal();
        return;
    }

    if (m_directory_for_saving.IsEmpty())
    {
        wxMessageDialog(this, wxT("Select directory for saving first."), wxT("Error"), wxICON_ERROR | wxOK).ShowModal();
        return;
    }

    m_generate_button->Disable();
    m_select_button->Disable();
    Update();
    MainPanel* parent = dynamic_cast<MainPanel*>(GetParent());
    parent->getCanvas()->generateLoadedAnimation(m_directory_for_saving);
    m_generate_button->Enable();
    m_select_button->Enable();
}
