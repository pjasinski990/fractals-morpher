#include <fstream>
#include "MainFrame.hpp"
#include "MainPanel.hpp"
#include "design.hpp"

MainFrame::MainFrame(wxString title):
        wxFrame(nullptr, wxID_ANY, title),
        m_main_panel{new MainPanel(this)},
        m_menu_bar{new wxMenuBar()},
        m_file_menu{new wxMenu()}
{
    m_file_menu->Append(Id::ID_LOAD, wxT("&Load"), wxT("Load fractal from file"));
    m_file_menu->Append(Id::ID_SAVE, wxT("&Save"), wxT("Save to file"));

    m_menu_bar->Append(m_file_menu, wxT("&File"));
    SetMenuBar(m_menu_bar);
    
    Bind(wxEVT_MENU, &MainFrame::onLoadMenuClicked, this, Id::ID_LOAD);
    Bind(wxEVT_MENU, &MainFrame::onSaveMenuClicked, this, Id::ID_SAVE);
}

MainFrame::~MainFrame() 
{
    Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onLoadMenuClicked, this, Id::ID_LOAD);
    Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::onSaveMenuClicked, this, Id::ID_SAVE);
}

Animation MainFrame::animation;

// TODO refactor this to some file handler
void MainFrame::onLoadMenuClicked(wxCommandEvent& e)
{
    wxFileDialog dialog(this, wxT("Load File"), wxEmptyString, 
            wxEmptyString, wxT("Data files (*.dat)|*.dat"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dialog.ShowModal() == wxID_CANCEL) {return;}

    std::ifstream fin(dialog.GetPath());
    if (!fin.is_open())
    {
        // handle, log error 
        std::cerr << "Error opening file to load" << std::endl;
        return;
    }

    fin >> animation.bitmap_size[0] >> animation.bitmap_size[1] >> animation.iter_count >> animation.is_3d;
    fin >> animation.observer_pos[0] >> animation.observer_pos[1] >> animation.observer_pos[2];
    fin >> animation.fractals_count;

    for (int i = 0; i < animation.fractals_count; i++)
    {
        auto ptr = std::make_shared<Fractal>();
        fin >> ptr->transform_count;
        for (int j = 0; j < ptr->transform_count; j++)
        {
            std::array<double, 6> arr;
            fin >> arr[0] >> arr[1] >> arr[2] >> arr[3] >> arr[4] >> arr[5];
            ptr->transformation.push_back(arr);
        }
        if (i != animation.fractals_count-1)  // if not last fractal
        {
            fin >> ptr->frames_for_animation;
        }
        if (i > 0)
        {
            animation.transformations_for_fractal.at(i-1)->next = ptr;
        }
        animation.transformations_for_fractal.push_back(ptr);
    }
    fin.close();
    e.Skip();
}

// TODO refactor this to some file handler
void MainFrame::onSaveMenuClicked(wxCommandEvent& e)
{
    wxFileDialog dialog(this, wxT("Save File"), wxEmptyString, 
            wxEmptyString, wxT("Data files (*.dat)|*.dat"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dialog.ShowModal() == wxID_CANCEL) {return;}

    std::ofstream fout(dialog.GetPath());
    if (!fout.is_open())
    {
        // handle, log error 
        std::cerr << "Error opening file to save" << std::endl;
        return;
    }

    fout << animation.bitmap_size[0] << " " << animation.bitmap_size[1] << " " << animation.iter_count << " " << animation.is_3d << std::endl;
    fout << animation.observer_pos[0] << " " << animation.observer_pos[1] << " " << animation.observer_pos[2] << std::endl;
    fout << animation.fractals_count << std::endl;

    for (int i = 0; i < animation.fractals_count; i++)
    {
        auto ptr = animation.transformations_for_fractal.at(i);
        fout << ptr->transform_count << std::endl;
        for (int j = 0; j < ptr->transform_count; j++)
        {
            auto arr = ptr->transformation.at(j);
            fout << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << " " << arr[4] << " " << arr[5] << std::endl;
        }
        if (i != animation.fractals_count-1)  // if not last fractal
        {
            fout << ptr->frames_for_animation << std::endl;
        }
    }
    fout.close();
    e.Skip();
}
