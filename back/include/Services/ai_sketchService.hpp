#pragma once
#include <string>

class ai_sketchService
{

public:
    static bool SketchToGenerate(const std::string &imagePath, const std::string &prompt);
};