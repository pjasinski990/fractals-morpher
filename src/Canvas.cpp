#include <wx/rawbmp.h>
#include "MainFrame.hpp"
#include "Canvas.hpp"
#include "design.hpp"
#include "config.hpp"

Canvas::Canvas(wxWindow* parent):
        wxPanel(parent)
{
    m_points_current.reserve(config::kpixels_max);
    m_points_transition.reserve(config::kpixels_max);
    m_points_next.reserve(config::kpixels_max);
    SetBackgroundColour(colors::canvas_color);
    Bind(wxEVT_PAINT, &Canvas::onPaintEvent, this);
}

Canvas::~Canvas()
{
    Unbind(wxEVT_PAINT, &Canvas::onPaintEvent, this);
}

void Canvas::onPaintEvent(wxPaintEvent& e)
{
    wxPaintDC dc(this);
    render(dc);
    e.Skip();
}

void Canvas::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void drawFractal(std::vector<wxPoint>& points, std::vector<std::array<double, 6>> transforms, const wxSize& screen_size, wxDC& dc)
{
    points[0].x = screen_size.GetWidth()/2;
    points[0].y = screen_size.GetHeight()/2;
    for (size_t i = 1; i < config::kpixels_max; i++)
    {
        int index = rand()%transforms.size();
        const auto& transformation = transforms.at(index);
        double a = transformation[0];
        double b = transformation[1];
        double c = transformation[2];
        double d = transformation[3];
        double t1 = transformation[4] * screen_size.GetX();
        double t2 = transformation[5] * screen_size.GetY();

        double newx = points[i-1].x*a + points[i-1].y*b + t1;
        double newy = points[i-1].x*c + points[i-1].y*d + t2;
        points[i].x = newx;
        points[i].y = newy;
        dc.DrawPoint(wxRealPoint(newx, newy));
    }
}

void Canvas::render(wxDC& dc)
{
    dc.Clear();
    int fractals_count = MainFrame::animation.fractals_count;
    if (fractals_count == 0) {return;}

    wxPoint starting_point(GetSize().x/2, GetSize().y/2);
    dc.DrawPoint(starting_point);

    auto trans1 = MainFrame::animation.fractals.at(0)->transformations;
    auto trans2 = MainFrame::animation.fractals.at(1)->transformations;
    drawFractal(m_points_current, trans2, GetSize(), dc);
}

void Canvas::onGenerateButtonClicked(wxCommandEvent& e)
{
    if (MainFrame::animation.fractals_count == 0)
    {
        wxMessageDialog(this, wxT("No fractal currently loaded."), wxT("Error"), wxICON_ERROR | wxOK).ShowModal();
        return;
    }

    wxDirDialog dialog(this, wxT("Select directory for saving"), wxGetCwd(), wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dialog.ShowModal() == wxID_CANCEL) {return;}

    wxBitmap bmp = wxBitmap(wxSize(GetSize()));
    bmp.SaveFile(dialog.GetPath() + ("/new_file_hello.png"), wxBITMAP_TYPE_PNG);
}

void Canvas::generateLoadedAnimation()
{

}