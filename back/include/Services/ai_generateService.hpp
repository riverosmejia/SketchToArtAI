#pragma once
#include <string>

class AiGenerate_service
{

public:
    static std::string generateImage(const std ::string &prompt, const std ::string &outputPath, const std ::string &modelId);
};
