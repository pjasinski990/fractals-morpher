#pragma once
#include <wx/wx.h>

class MainFrame: public wxFrame 
{
public:
	MainFrame(wxString title);
    ~MainFrame();

private:
    wxPanel* m_main_panel;
    wxPanel* m_canvas;
    wxMenuBar* m_menu_bar;
    wxMenu* m_file_menu;

};
