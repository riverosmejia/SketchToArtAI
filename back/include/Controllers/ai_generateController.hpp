#pragma once
#include <crow.h>

class AiGenerate_Controller
{

public:
    static crow::response generateImage(const crow::request &req);
};