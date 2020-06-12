#include <fstream>
#include "MainFrame.hpp"
#include "MainPanel.hpp"
#include "FileHandler.hpp"
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

Animation MainFrame::animation;

void MainFrame::onLoadMenuClicked(wxCommandEvent& e)
{
    wxFileDialog dialog(this, wxT("Load File"), wxEmptyString, 
            wxEmptyString, wxT("Data files (*.dat)|*.dat"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dialog.ShowModal() == wxID_CANCEL) {return;}

    try
    {
        animation = FileHandler::loadAnimationFromFile(dialog.GetPath());
        m_main_panel->setInfoText(animation.toString());
        m_main_panel->fillInputFields();
    }
    catch(const std::ios_base::failure& e)
    {
        std::cerr << e.what() << '\n';
    }
    e.Skip();
}

void MainFrame::onSaveMenuClicked(wxCommandEvent& e)
{
    if (MainFrame::animation.fractals_count == 0)
    {
        wxMessageDialog(this, wxT("No fractal currently loaded."), wxT("Error"), wxICON_ERROR | wxOK).ShowModal();
        return;
    }

    wxFileDialog dialog(this, wxT("Save File"), wxEmptyString, 
            wxEmptyString, wxT("Data files (*.dat)|*.dat"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dialog.ShowModal() == wxID_CANCEL) {return;}

    try
    {
        FileHandler::saveAnimationToFile(dialog.GetPath(), animation);
    }
    catch(const std::ios_base::failure& e)
    {
        std::cerr << e.what() << '\n';
    }
    e.Skip();
}
