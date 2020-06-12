#pragma once

#include <wx/wx.h>
#include "MenuPanel.hpp"
class Canvas;

class MainPanel: public wxPanel
{
public:
    MainPanel(wxWindow* parent);
    ~MainPanel();

    void setInfoText(const std::string& text);
    void fillInputFields() const {m_menu_panel->fillInputFields();}
    Canvas* getCanvas() {return m_canvas;}

private:
    Canvas* m_canvas;
    MenuPanel* m_menu_panel;
    wxTextCtrl* m_info;

};