#pragma once
#include <wx/wx.h>
#include <vector>
#include <array>
#include <memory>
typedef std::array<double, 6> transformation_t;

struct ColoredPoint
{
    ColoredPoint() = default;
    ColoredPoint(double x, double y, int color = -1): x{x}, y{y}, color_index{color} {}
    ColoredPoint(double x, double y, double z, int color = -1): x{x}, y{y}, z{z}, color_index{color} {}

    bool operator<(const ColoredPoint& o) {return color_index < o.color_index;}
    ColoredPoint& operator+=(const ColoredPoint& o);
    ColoredPoint& operator-=(const ColoredPoint& o);
    ColoredPoint& operator/=(int i);
    friend ColoredPoint operator+(ColoredPoint o1, const ColoredPoint& o2);
    friend ColoredPoint operator-(ColoredPoint o1, const ColoredPoint& o2);
    friend ColoredPoint operator/(ColoredPoint o, int i);

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    int color_index;
};

struct Fractal
{
    int transform_count;
    std::vector<transformation_t> transformations; // m transformation arrays for each fractal 
    int frames_for_animation; // frames for transition to next 

    int getRandomFunctionIndex() const;
    std::vector<ColoredPoint> generatePoints(unsigned int points_max, const wxSize& drawing_size) const;
    // void drawOnDC(wxDC& dc, const std::vector<ColoredPoint>& diffs);
};

struct Animation
{
    std::pair<int, int> bitmap_size;
    int iter_count;
    bool is_3d;
    std::array<double, 3> observer_pos;
    int fractals_count;
    std::vector<Fractal> fractals; // n for n fractals, each entry has m transformations

    std::string toString() const;
};
