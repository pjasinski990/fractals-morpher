#pragma once
#include <vector>
#include <wx/wx.h>

class ColorGenerator
{
public:
    static wxColor getNewColor();
    static std::vector<wxColor> getColorsVector(int count);
private:
    static wxColour hsvToRGB(double h, double s, double v);
    static double s_current_hue;
    static const double s_golden_ratio;
};