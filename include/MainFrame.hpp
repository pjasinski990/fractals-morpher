#pragma once
#include <wx/wx.h>
#include "Animation.h"

class MainFrame: public wxFrame 
{
public:
    static Animation animation;
	MainFrame(wxString title);
    ~MainFrame();

private:
    enum Id {ID_LOAD, ID_SAVE};
    wxPanel* m_main_panel;
    wxPanel* m_canvas;
    wxMenuBar* m_menu_bar;
    wxMenu* m_file_menu;

    void onLoadMenuClicked(wxCommandEvent& e);
    void onSaveMenuClicked(wxCommandEvent& e);
};
