#include "MenuPanel.hpp"
#include "MainFrame.hpp"
#include "design.hpp"

MenuPanel::MenuPanel(wxWindow* parent):
        wxPanel(parent),
        m_generate_button{new wxButton(this, wxID_ANY, wxT("Generate animation"))}
{
    SetBackgroundColour(colors::background_color_2);

    wxBoxSizer* sizer_main = new wxBoxSizer(wxVERTICAL);
    sizer_main->Add(m_generate_button, 0, wxALL | wxCENTER, 5);
    SetSizerAndFit(sizer_main);

    m_generate_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MenuPanel::onGenerateButtonClicked, this);
}

MenuPanel::~MenuPanel()
{
    m_generate_button->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &MenuPanel::onGenerateButtonClicked, this);
}

void MenuPanel::onGenerateButtonClicked(wxCommandEvent& e)
{
    if (MainFrame::animation.fractals_count == 0)
    {
        wxMessageDialog(this, wxT("No fractal currently loaded."), wxT("Error"), wxICON_ERROR | wxOK).ShowModal();
        return;
    }

    wxDirDialog dialog(this, wxT("Select directory for saving"), wxGetCwd(), wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dialog.ShowModal() == wxID_CANCEL) {return;}

    m_generate_button->Disable();
    Update();
    MainPanel* parent = dynamic_cast<MainPanel*>(GetParent());
    parent->getCanvas()->generateLoadedAnimation(dialog.GetPath());
    m_generate_button->Enable();
}
