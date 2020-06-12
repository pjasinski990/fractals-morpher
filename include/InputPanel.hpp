#pragma once

#include <wx/wx.h>
#include <array>
class Animation;

class InputPanel: public wxPanel
{
public:
    InputPanel(wxWindow* parent);
    void setInputFields();
    Animation getInputFields() const;

private:
    wxTextCtrl* m_bitmapsize_x;
    wxTextCtrl* m_bitmapsize_y;
    wxTextCtrl* m_points_count;

    wxTextCtrl* m_f1_tcount;
    wxTextCtrl* m_f2_tcount;
    wxTextCtrl* m_frames_to_second;
    std::array<std::array<wxTextCtrl*, 6>, 5> m_transforms1;
    std::array<std::array<wxTextCtrl*, 6>, 5> m_transforms2;

    wxButton* m_save_button;
    void onSaveButtonClicked(wxCommandEvent& e);
};