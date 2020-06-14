#include "ColorGenerator.hpp"
#include "design.hpp"
#include <iostream>

double ColorGenerator::s_current_hue = 0.0;
const double ColorGenerator::s_golden_ratio = 0.618033988749895;

wxColor ColorGenerator::hsvToRGB(double h, double s, double v)
{
    int h_i = static_cast<int>(6.0 * h);
    double f = 6 * h - h_i;
    double p = v * (1 - s);
    double q = v * (1 - f*s);
    double t = v * (1 - (1 - f)*s);

    double r, g, b;
    switch (h_i)
    {
    case 0:
        r = v;
        g = t;
        b = p;
        break;

    case 1:
        r = q;
        g = v;
        b = p;
        break;

    case 2:
        r = p;
        g = v;
        b = t;
        break;

    case 3:
        r = p;
        g = q;
        b = v;
        break;

    case 4:
        r = t;
        g = p;
        b = v;
        break;

    case 5:
        r = v;
        g = p;
        b = q;
        break;
    default:
        r = 0.0;
        g = 0.0;
        b = 0.0;
        break;
    }
    return wxColor(r*255.0, g*255.0, b*255.0);
}

wxColour ColorGenerator::getNewColor()
{
    if (s_current_hue == 0.0)
    {
        srand(time(0));
        s_current_hue = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    }
    else
    {
        s_current_hue += s_golden_ratio;
        s_current_hue = fmod(s_current_hue, 1.0);
    }
    return hsvToRGB(s_current_hue, design_constants::ksaturation, design_constants::kvalue);
}

std::vector<wxColor> ColorGenerator::getColorsVector(int count)
{
    std::vector<wxColor> colors_vec;
    for (int i = 0; i < count; i++)
    {
        auto color = ColorGenerator::getNewColor();
        colors_vec.push_back(ColorGenerator::getNewColor());
    }
    return colors_vec;
}