#pragma once
#include <wx/wx.h>
#include "MainPanel.hpp"
#include "Animation.hpp"

class MainFrame: public wxFrame 
{
public:
    static Animation animation;
	MainFrame(wxString title);
    ~MainFrame();

private:
    enum Id {ID_LOAD, ID_SAVE};
    MainPanel* m_main_panel;
    wxMenuBar* m_menu_bar;
    wxMenu* m_file_menu;

    void onLoadMenuClicked(wxCommandEvent& e);
    void onSaveMenuClicked(wxCommandEvent& e);
};
