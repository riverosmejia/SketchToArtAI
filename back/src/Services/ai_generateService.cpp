#include <Services/ai_generateService.hpp>
#include <stdlib.h>
#include <iostream>

bool AiGenerate_service::generateImage(const std::string &prompt, const std::string &outputPath, const std::string &modelId)
{

    std::string safePrompt = "\"" + prompt + "\"";
    std::string safeOutput = "\"" + outputPath + "\"";
    std::string safeModel = "\"" + modelId + "\"";

    // Comando para ejecutar el script de Python ubicado en Scripts

    std::string command = "python3 Scripts/generate.py --prompt " + safePrompt +
                          " --filename " + safeOutput +
                          " --model " + safeModel;

    std::cout << "ejecutando el comando" + command + ".\n";

    int result = system(command.c_str());

    return result == 0;
}