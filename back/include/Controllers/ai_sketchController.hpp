#pragma once
#include <crow.h>

class ai_sketchController
{

public:
    static crow::response sketchImage(const crow::request &req);
};