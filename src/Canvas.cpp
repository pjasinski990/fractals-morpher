#include <iomanip>
#include "MainFrame.hpp"
#include "Canvas.hpp"
#include "design.hpp"

Canvas::Canvas(wxWindow* parent):
        wxPanel(parent)
{
    SetBackgroundColour(colors::canvas_color);
}

void Canvas::generateLoadedAnimation(const wxString& dir_path)
{
    wxClientDC dc(this);
    try
    {
        auto bitmaps = MainFrame::animation.generateBitmaps(dc, GetSize());
        int i = 0;
        for (auto&& bitmap: bitmaps)
        {
            std::stringstream ss;
            ss<< std::setw(3) << std::setfill('0') << i++;
            std::string filename = "/frame" + ss.str() + ".png";
            bitmap.SaveFile(dir_path + filename, wxBITMAP_TYPE_PNG);
        }
    }
    catch(const std::exception& e)
    {
        wxMessageDialog(this, wxT("3D not supported yet"), wxT("Error"), wxICON_ERROR | wxOK).ShowModal();
    }
}
