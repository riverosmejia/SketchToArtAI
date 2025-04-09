#pragma once
#include <string>

class AiGenerate_service
{

public:
    static bool generateImage(const std ::string &prompt, const std ::string &outputPath, const std ::string &modelId);
};
