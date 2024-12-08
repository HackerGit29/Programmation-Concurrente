#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include "client.h"
#include "order.h"



class ClientController : public QObject {
    Q_OBJECT

public:
    ClientController(Client* model, QObject* parent = nullptr);

    void moveToTable(QGraphicsPixmapItem* tableItem);
    void placeOrder();
    void finishMeal();
    void leaveRestaurant();
    Client* findClientById(int clientId);
    void addClient(Client* newClient);


private:
    Client* model;
    Order *orderModel;

    void simulateConsumptionTime();
    QList<Client*> clients;

};

#endif // CLIENTCONTROLLER_H
