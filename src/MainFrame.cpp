#include "MainFrame.hpp"
#include "MainPanel.hpp"
#include "design.hpp"

MainFrame::MainFrame(wxString title):
        wxFrame(nullptr, wxID_ANY, title),
        m_main_panel{new MainPanel(this)},
        m_menu_bar{new wxMenuBar()},
        m_file_menu{new wxMenu()}
{
    m_file_menu->Append(Id::ID_LOAD, wxT("&Load"), wxT("Load fractal from file"));
    m_file_menu->Append(Id::ID_SAVE, wxT("&Save"), wxT("Save to file"));

    m_menu_bar->Append(m_file_menu, wxT("&File"));
    SetMenuBar(m_menu_bar);
    
    Bind(wxEVT_MENU, &MainFrame::onLoadMenuClicked, this, Id::ID_LOAD);
    Bind(wxEVT_MENU, &MainFrame::onSaveMenuClicked, this, Id::ID_SAVE);
}

MainFrame::~MainFrame() 
{
    Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onLoadMenuClicked, this, Id::ID_LOAD);
    Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onSaveMenuClicked, this, Id::ID_SAVE);
}

void MainFrame::onLoadMenuClicked(wxCommandEvent& e)
{
    wxFileDialog* dialog = new wxFileDialog(this, wxT("Load File"));
    dialog->ShowModal();

    e.Skip();
}

void MainFrame::onSaveMenuClicked(wxCommandEvent& e)
{
    e.Skip();
}
