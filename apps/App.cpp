#include "App.hpp"

IMPLEMENT_APP(App);
DECLARE_APP(App);

bool App::OnInit()
{
	m_main_frame = new MainFrame(wxT("Fractals"));
	m_main_frame->SetSize(wxSize(1200, 800));
	m_main_frame->Center();
	m_main_frame->Show(true);
	m_main_frame->SetFocus();

	return true;
}