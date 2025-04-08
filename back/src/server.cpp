#include "server.hpp"
#include "Routes/index_routes.hpp" // Agrega tus rutas aquí

Server::Server()
{
    setupRoutes(); // ✅ ¡Así está bien!
}

void Server::run()
{

    app.port(18080).multithreaded().run(); // iniciar servidor en puerto 18080
}

void Server::setupRoutes()
{

    setupIndexRoutes(app); // iniciar rutas por el index de rutas
}
