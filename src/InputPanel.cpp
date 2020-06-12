#include "InputPanel.hpp"
#include "design.hpp"
#include "MainFrame.hpp"
#include "MainPanel.hpp"
#include "Animation.hpp"
#include "Fractal.hpp"

InputPanel::InputPanel(wxWindow* parent): wxPanel(parent),
        m_bitmapsize_x{new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_DIGITS))},
        m_bitmapsize_y{new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_DIGITS))},
        m_points_count{new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_DIGITS))},
        m_f1_tcount{new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_DIGITS))},
        m_f2_tcount{new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_DIGITS))},
        m_frames_to_second{new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_DIGITS))},
        m_save_button{new wxButton(this, wxID_ANY, wxT("Save"))}
{
    wxBoxSizer* sizer_main = new wxBoxSizer(wxVERTICAL);

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
    for (auto&& t: m_transforms1)
    {
        wxBoxSizer* s = new wxBoxSizer(wxHORIZONTAL);
        s->Add(new wxStaticText(this, wxID_ANY, "T" + std::to_string(++k)));
        for (auto&& field: t)
        {
            field = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_NUMERIC));
            field->SetMaxSize(wxSize(65, 25));
            s->Add(field);
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
    for (auto&& t: m_transforms2)
    {
        wxBoxSizer* s = new wxBoxSizer(wxHORIZONTAL);
        s->Add(new wxStaticText(this, wxID_ANY, "T" + std::to_string(++k)));
        for (auto&& field: t)
        {
            field = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0L, wxTextValidator(wxFILTER_NUMERIC));
            field->SetMaxSize(wxSize(65, 25));
            s->Add(field);
        }
        sizer_transforms2->Add(s);
    }

    sizer_f2->Add(sizer_transforms2);
    sizer_main->Add(sizer_f2, 0, wxALL | wxEXPAND, 5);


    sizer_main->Add(m_save_button, 0, wxCENTER | wxALL, 5);
    SetSizerAndFit(sizer_main);

    m_save_button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &InputPanel::onSaveButtonClicked, this);
}

void InputPanel::onSaveButtonClicked(wxCommandEvent& e)
{
    MainFrame::animation = getInputFields();
    MenuPanel* q = dynamic_cast<MenuPanel*>(GetParent());
    if (q)
    {
        MainPanel* mainq = dynamic_cast<MainPanel*>(q->GetParent());
        if (mainq)
        {
            mainq->setInfoText(MainFrame::animation.toString());
        }
    }
}

void InputPanel::setInputFields()
{
    auto a = MainFrame::animation;
    
    m_bitmapsize_x->SetValue(std::to_string(a.bitmap_size.GetWidth()));
    m_bitmapsize_y->SetValue(std::to_string(a.bitmap_size.GetHeight()));
    m_points_count->SetValue(std::to_string(a.iter_count));
    m_f1_tcount->SetValue(std::to_string(a.fractals[0].transform_count));
    m_f2_tcount->SetValue(std::to_string(a.fractals[1].transform_count));
    m_frames_to_second->SetValue(std::to_string(a.fractals[0].frames_for_animation));

    const Fractal& f1 = a.fractals[0];
    const Fractal& f2 = a.fractals[1];
    for (int i = 0; i < f1.transform_count; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            m_transforms1[i][j]->SetValue(std::to_string(f1.transformations[i][j]));
        }
    }
    for (int i = 0; i < f2.transform_count; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            m_transforms2[i][j]->SetValue(std::to_string(f2.transformations[i][j]));
        }
    }
}

Animation InputPanel::getInputFields() const
{
    Animation a;
    a.is_3d = 0;
    a.fractals_count = 2;

    a.bitmap_size.SetWidth(wxAtoi(m_bitmapsize_x->GetValue()));
    a.bitmap_size.SetHeight(wxAtoi(m_bitmapsize_y->GetValue()));
    a.iter_count = wxAtoi(m_points_count->GetValue());

    Fractal f1;
    f1.transform_count = wxAtoi(m_f1_tcount->GetValue());
    f1.frames_for_animation = wxAtoi(m_frames_to_second->GetValue());
    for (int i = 0; i < f1.transform_count; i++)
    {
        std::array<double, 6> transform;
        for (int j = 0; j < 6; j++)
        {
            transform[j] = wxAtof(m_transforms1[i][j]->GetValue());
        }
        f1.transformations.push_back(transform);
    }
    a.fractals.push_back(f1);

    Fractal f2;
    f2.transform_count = wxAtoi(m_f2_tcount->GetValue());
    for (int i = 0; i < f2.transform_count; i++)
    {
        std::array<double, 6> transform;
        for (int j = 0; j < 6; j++)
        {
            transform[j] = wxAtof(m_transforms2[i][j]->GetValue());
        }
        f2.transformations.push_back(transform);
    }
    a.fractals.push_back(f2);

    return a;
}