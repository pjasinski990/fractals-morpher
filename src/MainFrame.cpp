#include "MainFrame.hpp"
#include "MainPanel.hpp"
#include "design.hpp"

MainFrame::MainFrame(wxString title):
        wxFrame(nullptr, wxID_ANY, title),
        m_main_panel{new MainPanel(this)},
        m_menu_bar{new wxMenuBar()},
        m_file_menu{new wxMenu()}
{
    m_file_menu->Append(wxID_ANY, wxT("&Load"), wxT("Load fractal( from file"));
    m_file_menu->Append(wxID_ANY, wxT("&Save"), wxT("Save to file"));

    m_menu_bar->Append(m_file_menu, wxT("&File"));
    SetMenuBar(m_menu_bar);

}

MainFrame::~MainFrame() = default;
