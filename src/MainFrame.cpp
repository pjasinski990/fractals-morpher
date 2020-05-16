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

void MainFrame::onLoadMenuClicked(wxCommandEvent& e)
{
    wxFileDialog dialog(this, wxT("Load File"), wxEmptyString, 
            wxEmptyString, wxT("Data files (*.dat)|*.dat"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dialog.ShowModal() == wxID_CANCEL) {return;}

    std::ifstream fin(dialog.GetPath());
    if (!fin.is_open())
    {
        // handle, log error 
        return;
    }

    fin >> m_transform.bitmap_size[0] >> m_transform.bitmap_size[1] >> m_transform.iter_count >> m_transform.is_3d;
    fin >> m_transform.observer_pos[0] >> m_transform.observer_pos[1] >> m_transform.observer_pos[2];
    fin >> m_transform.fractals_count;

    for (int i = 0; i < m_transform.fractals_count; i++)
    {
        auto ptr = std::make_shared<Transformation>();
        fin >> ptr->transform_count;
        for (int j = 0; j < ptr->transform_count; j++)
        {
            std::array<double, 6> arr;
            fin >> arr[0] >> arr[1] >> arr[2] >> arr[3] >> arr[4] >> arr[5];
            // std::cout << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << " " << arr[4] << " " << arr[5] << std::endl;
            ptr->transformation.push_back(arr);
        }
        if (i != m_transform.fractals_count-1)  // if not last fractal
        {
            fin >> ptr->frames_for_animation;
            // std::cout << "frames for animation " << i << ": " << ptr->frames_for_animation << std::endl;
        }
        if (i > 0)
        {
            m_transform.transformations_for_fractal.at(i-1)->next = ptr;
        }
        m_transform.transformations_for_fractal.push_back(ptr);
    }
    fin.close();
    e.Skip();
}

void MainFrame::onSaveMenuClicked(wxCommandEvent& e)
{
    wxFileDialog dialog(this, wxT("Save File"), wxEmptyString, 
            wxEmptyString, wxT("Data files (*.dat)|*.dat"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dialog.ShowModal() == wxID_CANCEL) {return;}

    std::ofstream fout(dialog.GetPath());
    if (!fout.is_open())
    {
        // handle, log error 
        return;
    }

    // TODO save to file
    
    fout.close();
    e.Skip();
}
