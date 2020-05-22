#pragma once
#include "Animation.hpp"

class FileHandler
{
public:
    static Animation loadAnimationFromFile(const char* file_path);
    static void saveAnimationToFile(const char* file_path, const Animation& animation);

private:

};
