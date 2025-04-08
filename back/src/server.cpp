#include "server.h"

void start_server()
{

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]()

                         { return "Servidor funcionando!"; }

    );

    app.port(8080).multithreaded().run(); // Iniciar el servidor
}