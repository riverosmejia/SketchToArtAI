#include "Controllers/ai_generateController.hpp"
#include <cstdlib>
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

        bool pet = AiGenerate_service::generateImage(prompt, output, model);

        if (pet)
        {

            return crow::response(200, "imagen generada exitosamente.\n");
        }
        else
        {

            return crow::response(400, "Error al generar imagen.\n");
        }
    }
    catch (const std::exception &e)
    {
        return crow::response(400, std::string("Error al procesar la petición: ") + e.what());
    }
}