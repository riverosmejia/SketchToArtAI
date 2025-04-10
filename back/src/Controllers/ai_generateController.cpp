#include "Controllers/ai_generateController.hpp"
#include "Services/ai_generateService.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

crow::response AiGenerate_Controller::generateImage(const crow::request &req)
{
    try
    {
        auto body = json::parse(req.body);

        std::string prompt = body["prompt"];
        std::string output = body.value("output", "output.png");
        std::string model = body.value("model", "CompVis/stable-diffusion-v1-4");

        // Llama al servicio y recibe la imagen como string binario
        std::string imageBinary = AiGenerate_service::generateImage(prompt, output, model);

        if (!imageBinary.empty())
        {
            crow::response res;
            res.code = 200;
            res.set_header("Content-Type", "image/png");
            res.body = std::move(imageBinary);
            return res;
        }
        else
        {
            return crow::response(500, "Error al generar la imagen.\n");
        }
    }
    catch (const std::exception &e)
    {
        return crow::response(400, std::string("Error al procesar la petición: ") + e.what());
    }
}
