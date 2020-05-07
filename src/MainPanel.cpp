#include "MainPanel.hpp"
#include "Canvas.hpp"
#include "MenuPanel.hpp"

#include "design.hpp"

MainPanel::MainPanel(wxWindow* parent): 
        wxPanel(parent),
        m_canvas{new Canvas(this)},
        m_menu_panel{new MenuPanel(this)}
{
    SetBackgroundColour(colors::background_color_1);

    wxBoxSizer* sizer_main = new wxBoxSizer(wxHORIZONTAL);

    sizer_main->Add(m_canvas, 1, wxEXPAND | wxALL, 5);
    sizer_main->Add(m_menu_panel, 0, wxALL, 5);

    SetSizerAndFit(sizer_main);

}

MainPanel::~MainPanel() = default;
