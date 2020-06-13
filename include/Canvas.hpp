#pragma once

#include <wx/wx.h>
#include "Animation.hpp"

class Canvas: public wxPanel
{
public:
    Canvas(wxWindow* parent);
    void generateLoadedAnimation(const wxString& dir_path);

private:

};
