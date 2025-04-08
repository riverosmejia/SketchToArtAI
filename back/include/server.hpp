#pragma once

#include <crow.h>

class Server
{

public:
    Server();   // constructor
    void run(); // iniciar el server

private:
    crow::SimpleApp app; // Intancia de Crow :p
    void setupRoutes();  // setup de rutas
};