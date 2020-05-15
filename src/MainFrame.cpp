#include <fstream>
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
    wxFileDialog dialog(this, wxT("Load File"), wxEmptyString, 
            wxEmptyString, wxT("Data files (*.dat)|*.dat"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dialog.ShowModal() == wxID_CANCEL) {return;}

    std::fstream fstream(dialog.GetPath());

    fstream >> m_transform.bitmap_size[0] >> m_transform.bitmap_size[1] >> m_transform.iter_count, m_transform.is_3d;

    e.Skip();
}

void MainFrame::onSaveMenuClicked(wxCommandEvent& e)
{
    wxFileDialog dialog(this, wxT("Save File"), wxEmptyString, 
            wxEmptyString, wxT("Data files (*.dat)|*.dat"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dialog.ShowModal() == wxID_CANCEL) {return;}

    std::fstream fstream(dialog.GetPath());

    // TODO save to file
    
    e.Skip();
}
