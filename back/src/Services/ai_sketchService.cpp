#include "Services/ai_sketchService.hpp"
#include <cstdlib>
#include <sstream>

bool ai_sketchService::SketchToGenerate(const std::string &imagePath, const std::string &prompt)
{
    std::stringstream command;

    // Escapamos comillas por si el prompt es complejo
    std::string safePrompt = prompt;
    size_t pos = 0;
    while ((pos = safePrompt.find("\"", pos)) != std::string::npos)
    {
        safePrompt.replace(pos, 1, "\\\"");
        pos += 2;
    }

    command << "python3 Scripts/generate_from_sketch.py"
            << " --sketch \"" << imagePath << "\""
            << " --prompt \"" << safePrompt << "\"";

    int result = std::system(command.str().c_str());

    return result == 0;
}
