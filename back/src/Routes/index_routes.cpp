#include "Routes/index_routes.hpp"
#include <Controllers/index_controllers.hpp>

void setupIndexRoutes(crow::SimpleApp &app)
{
    CROW_ROUTE(app, "/hello")([]()
                              { return getWelcomeMessage(); });
}