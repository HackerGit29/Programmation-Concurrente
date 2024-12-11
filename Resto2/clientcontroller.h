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
    void addClient(Client* newClient);
    Client* findClientById(int clientId);




private:
    Client* model;
    Order *orderModel;

    void simulateConsumptionTime();
    QList<Client*> clients;

};

#endif // CLIENTCONTROLLER_H
