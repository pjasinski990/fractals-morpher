#include "InputPanel.hpp"
#include "design.hpp"

InputPanel::InputPanel(wxWindow* parent): wxScrolledWindow(parent),
        m_bitmapsize_x{new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_DIGITS))},
        m_bitmapsize_y{new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_DIGITS))},
        m_points_count{new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_DIGITS))},
        m_f1_tcount{new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_DIGITS))},
        m_f2_tcount{new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_DIGITS))},
        m_frames_to_second{new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_DIGITS))},
        m_save_button{new wxButton(this, wxID_ANY, wxT("Save"))}
{
    wxBoxSizer* sizer_main = new wxBoxSizer(wxVERTICAL);
    SetScrollbar(20, 20, 50, 50);

    // Bitmap size
    wxStaticBoxSizer* sizer_size = new wxStaticBoxSizer(wxHORIZONTAL, this, static_text::bitmap_size_label);
    sizer_size->Add(m_bitmapsize_x, 1);
    sizer_size->Add(m_bitmapsize_y, 1);
    sizer_main->Add(sizer_size, 0, wxALL | wxEXPAND, 5);

    // Points count
    wxStaticBoxSizer* sizer_points = new wxStaticBoxSizer(wxHORIZONTAL, this, static_text::points_count_label);
    sizer_points->Add(m_points_count, 1);
    sizer_main->Add(sizer_points, 0, wxALL | wxEXPAND, 5);

    // 1st fractal
    wxStaticBoxSizer* sizer_f1 = new wxStaticBoxSizer(wxVERTICAL, this, static_text::fractal1_label);
    sizer_f1->Add(new wxStaticText(this, wxID_ANY, static_text::transform_count_label));
    sizer_f1->Add(m_f1_tcount, 0, wxCENTER);
    wxStaticBoxSizer* sizer_transforms1 = new wxStaticBoxSizer(wxVERTICAL, this, static_text::transforms_label);

    int k = 0;
    for (auto && o: m_transforms1)
    {
        wxBoxSizer* s = new wxBoxSizer(wxHORIZONTAL);
        s->Add(new wxStaticText(this, wxID_ANY, "T" + std::to_string(++k)));
        for (size_t i = 0; i < 6; i++)
        {
            o = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_NUMERIC));
            o->SetMaxSize(wxSize(45, 25));
            s->Add(o);
        }
        sizer_transforms1->Add(s);
    }
    

    sizer_f1->Add(sizer_transforms1);
    sizer_main->Add(sizer_f1, 0, wxALL | wxEXPAND, 5);

    // Frames count
    wxStaticBoxSizer* sizer_frames_count = new wxStaticBoxSizer(wxVERTICAL, this, static_text::frames_to_second_label);
    sizer_frames_count->Add(m_frames_to_second, 0, wxCENTER);
    sizer_main->Add(sizer_frames_count, 0, wxALL | wxEXPAND, 5);
    

    // 2nd fractal
    wxStaticBoxSizer* sizer_f2 = new wxStaticBoxSizer(wxVERTICAL, this, static_text::fractal2_label);
    sizer_f2->Add(new wxStaticText(this, wxID_ANY, static_text::transform_count_label));
    sizer_f2->Add(m_f2_tcount, 0, wxCENTER);
    wxStaticBoxSizer* sizer_transforms2 = new wxStaticBoxSizer(wxVERTICAL, this, static_text::transforms_label);

    k = 0;
    for (auto && o: m_transforms2)
    {
        wxBoxSizer* s = new wxBoxSizer(wxHORIZONTAL);
        s->Add(new wxStaticText(this, wxID_ANY, "T" + std::to_string(++k)));
        for (size_t i = 0; i < 6; i++)
        {
            o = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_NUMERIC));
            o->SetMaxSize(wxSize(45, 25));
            s->Add(o);
        }
        sizer_transforms2->Add(s);
    }

    sizer_f2->Add(sizer_transforms2);
    sizer_main->Add(sizer_f2, 0, wxALL | wxEXPAND, 5);


    sizer_main->Add(m_save_button, 0, wxCENTER | wxALL, 5);
    SetSizerAndFit(sizer_main);
}

//wxFILTER_NUMERIC