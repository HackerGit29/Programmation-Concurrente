#include "clientcontroller.h"

void ClientController::addClient(Client *client) {
    clients.append(client);
}

void ClientController::moveClient(int clientId, int x, int y, double scale) {
    for (Client *client : clients) {
        if (client->getId() == clientId) {
            client->setPosition(x, y, scale);
            break;
        }
    }
}

Client *ClientController::findClientById(int clientId) {
    for (Client *client : clients) {
        if (client->getId() == clientId) {
            return client;
        }
    }
    return nullptr;
}
