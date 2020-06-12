#pragma once

#include <wx/wx.h>
#include <array>
class Animation;

class InputPanel: public wxPanel
{
public:
    InputPanel(wxWindow* parent);
    void setInputFields();
    Animation getInputFields();

private:
    wxTextCtrl* m_bitmapsize_x;
    wxTextCtrl* m_bitmapsize_y;
    wxTextCtrl* m_points_count;

    wxTextCtrl* m_f1_tcount;
    wxTextCtrl* m_f2_tcount;
    std::array<wxTextCtrl*, 5> m_transforms1;
    std::array<wxTextCtrl*, 5> m_transforms2;
};