#include "Controllers/ai_sketchController.hpp"
#include "Services/ai_sketchService.hpp"
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;    // biblioteca para archivos json
namespace fs = std::filesystem; // biblioteca del sist. para crear archivos y carpetas

crow::response ai_sketchController::sketchImage(const crow::request &req)
{

    try
    {
        //
        //
        // Verificar que sea una petición multipart (osea de archivos)

        if (req.get_header_value("Content-Type").find("multipart/form-data") == std::string::npos)
        {
            return crow::response(400, "Formato incorrecto. Se esperaba multipart/form-data.\n");
        }

        std::string body = req.body;

        //
        //
        // Buscar los delimitadores y el nombre del archivo
        std::size_t start = body.find("filename=\"");

        if (start == std::string::npos)
            return crow::response(400, "No se encontró archivo.\n");

        std::size_t filename_start = start + 10;
        std::size_t filename_end = body.find("\"", filename_start);
        std::string filename = body.substr(filename_start, filename_end - filename_start);

        std::string output_path = "sketches/" + filename;

        //
        //
        // Buscar el contenido del archivo (después de \r\n\r\n)
        std::size_t file_data_start = body.find("\r\n\r\n", filename_end);
        if (file_data_start == std::string::npos)
            return crow::response(400, "No se pudo leer la imagen.\n");

        file_data_start += 4;
        std::size_t file_data_end = body.rfind("------");

        std::string file_data = body.substr(file_data_start, file_data_end - file_data_start);

        //
        //
        // Guardar el archivo en el directorio de sketches

        fs::create_directories("sketches");
        std::ofstream out(output_path, std::ios::binary);
        out.write(file_data.c_str(), file_data.size());
        out.close();

        //
        //
        // Buscar el prompt (simple para ahora, se puede mejorar luego)
        std::string prompt;
        std::size_t prompt_pos = body.find("name=\"prompt\"");
        if (prompt_pos != std::string::npos)
        {
            std::size_t value_start = body.find("\r\n\r\n", prompt_pos);
            value_start += 4;
            std::size_t value_end = body.find("------", value_start);
            prompt = body.substr(value_start, value_end - value_start);
        }
        else
        {
            return crow::response(400, "No se encontró el campo prompt.\n");
        }

        //
        //
        // Llamar al servicio
        bool success = ai_sketchService::SketchToGenerate(output_path, prompt);

        if (success)
        {
            return crow::response(200, "Imagen generada exitosamente.\n");
        }
        else
        {
            return crow::response(500, "Error al generar la imagen.\n");
        }
    }
    catch (const std::exception &e)
    {
        return crow::response(500, std::string("Error interno: ") + e.what());
    }
}