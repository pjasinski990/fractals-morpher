#include "MainPanel.hpp"
#include "Canvas.hpp"
#include "MenuPanel.hpp"

#include "design.hpp"

MainPanel::MainPanel(wxWindow* parent): 
        wxPanel(parent),
        m_canvas{new Canvas(this)},
        m_menu_panel{new MenuPanel(this)},
        m_info{new wxTextCtrl(this, wxID_ANY, wxEmptyString, 
                wxDefaultPosition, wxDefaultSize, 
                wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH)}
{
    SetBackgroundColour(colors::background_color_1);
    m_info->SetMinSize(wxSize(0, 120));
    m_info->AppendText(wxT("No file loaded"));

    wxBoxSizer* sizer_horiz = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_main = new wxBoxSizer(wxVERTICAL);

    sizer_horiz->Add(m_canvas, 1, wxEXPAND | wxLEFT | wxUP, 5);
    sizer_horiz->Add(m_menu_panel, 0, wxALL, 5);

    sizer_main->Add(sizer_horiz, 1, wxEXPAND);
    sizer_main->Add(m_info, 0, wxEXPAND | wxALL, 5);

    SetSizerAndFit(sizer_main);
}

MainPanel::~MainPanel() = default;

void MainPanel::setInfoText(const std::string& text)
{
    m_info->Clear();
    m_info->AppendText(text);
    m_info->ShowPosition(0);
}
