#include <Services/ai_generateService.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

std::string AiGenerate_service::generateImage(const std::string &prompt, const std::string &outputFilename, const std::string &modelId)
{
    std::string filename = outputFilename.empty() ? "output.png" : outputFilename;
    if (filename.find('.') == std::string::npos)
    {
        filename += ".png";
    }

    std::string outputPath = filename;
    // 🔥 Limpiar carpeta "generated"
    try
    {
        for (const auto &entry : fs::directory_iterator("generated"))
        {
            fs::remove_all(entry.path());
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error al limpiar la carpeta 'generated': " << e.what() << std::endl;
        return "";
    }

    // 🧪 Preparar los argumentos seguros
    std::string safePrompt = "\"" + prompt + "\"";
    std::string safeOutput = "\"" + outputPath + "\"";
    std::string safeModel = "\"" + modelId + "\"";

    // 🐍 Ejecutar script Python
    std::string command = "python3 Scripts/generate.py --prompt " + safePrompt +
                          " --filename " + safeOutput +
                          " --model " + safeModel;

    std::cout << "ejecutando el comando: " << command << std::endl;

    int result = system(command.c_str());
    if (result != 0)
    {
        std::cerr << "Error al ejecutar el script de Python." << std::endl;
        return "";
    }

    // 🖼 Leer la imagen generada como binario
    std::ifstream file("generated/" + outputFilename, std::ios::binary);
    if (!file)
    {
        std::cerr << "No se pudo abrir el archivo generado." << std::endl;
        return "";
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
