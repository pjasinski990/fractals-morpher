#pragma once

#include <wx/wx.h>
#include "MainFrame.hpp"

class App: public wxApp
{
public:
	bool OnInit() override;

private:
    MainFrame* m_main_frame;
};