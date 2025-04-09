#include "Routes/index_routes.hpp"
#include <Controllers/index_controllers.hpp>
#include <Controllers/ai_generateController.hpp>
#include <Controllers/ai_sketchController.hpp>

void setupIndexRoutes(crow::SimpleApp &app)
{
    CROW_ROUTE(app, "/")([]()
                         { return getWelcomeMessage(); });

    CROW_ROUTE(app, "/generateImage").methods("POST"_method)([](const crow::request &req)
                                                             { return AiGenerate_Controller::generateImage(req); });

    CROW_ROUTE(app, "/SketchImage").methods("POST"_method)([](const crow::request &req)
                                                           { return ai_sketchController::sketchImage(req); });
}