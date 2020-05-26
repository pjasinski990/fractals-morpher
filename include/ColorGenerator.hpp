#pragma once
#include <wx/wx.h>

class ColorGenerator
{
public:
    static wxColor getNewColor();
private:
    static wxColour hsvToRGB(double h, double s, double v);
    static double s_current_hue;
    static const double s_golden_ratio;
};