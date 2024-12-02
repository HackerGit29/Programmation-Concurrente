// clientcontroller.h
#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QVector>
#include "client.h"

class ClientController {
public:
    void addClient(Client *client);
    void moveClient(int clientId, int x, int y, double scale = 100.0);
    Client *findClientById(int clientId);

private:
    QVector<Client*> clients; // Liste des clients dans la salle
};

#endif // CLIENTCONTROLLER_H
