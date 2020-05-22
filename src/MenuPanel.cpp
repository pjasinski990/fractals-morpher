#include "MenuPanel.hpp"
#include "design.hpp"

MenuPanel::MenuPanel(wxWindow* parent):
        wxPanel(parent),
        m_2dbutton{new wxButton(this, wxID_ANY, wxT("2D"))},
        m_3dbutton{new wxButton(this, wxID_ANY, wxT("3D"))}
{
    SetBackgroundColour(colors::background_color_2);
    wxBoxSizer* sizer_main = new wxBoxSizer(wxVERTICAL);

    sizer_main->Add(m_2dbutton, 0, wxALL | wxCENTER, 5);
    sizer_main->Add(m_3dbutton, 0, wxALL | wxCENTER, 5);

    SetSizerAndFit(sizer_main);
}

MenuPanel::~MenuPanel() = default;