#include "clientcontroller.h"
#include <QTimer>

ClientController::ClientController(Client* model, QObject* parent)
    : QObject(parent), model(model) {}



void ClientController::addClient(Client* newClient) {
    clients.append(newClient);
}


void ClientController::moveToTable(QGraphicsPixmapItem* tableItem) {
    if (!model->getIsSeated()) {
        model->moveToPosition(tableItem->pos());
        model->setSeated(true);

        // Déclencher la prise de commande après 2 secondes
        QTimer::singleShot(2000, this, &ClientController::placeOrder);
    }
}



Client* ClientController::findClientById(int clientId) {
    for (Client* client : clients) {
        if (client->getId() == clientId) {
            return client;
        }
    }
    return nullptr;
}



void ClientController::placeOrder() {
    if (!model->getHasOrdered()) {
        model->setHasOrdered(true);
        emit model->orderPlaced(model->getGroupSize());

        // Simuler la consommation
        simulateConsumptionTime();
    }
}

void ClientController::simulateConsumptionTime() {
    int consumptionTime = (model->getGroupSize() > 4) ? 60000 : 5000; // Temps selon la taille du groupe
    QTimer::singleShot(consumptionTime, this, &ClientController::finishMeal);
}

void ClientController::finishMeal() {
    if (model->getIsConsuming()) {
        model->setConsuming(false);
        emit model->mealFinished();

        // Suppression de la commande une fois terminée
        orderModel->removeOrder(model->getId());
    }
}

void ClientController::leaveRestaurant() {
    if (model->getIsConsuming()) {
        model->removeFromScene();
        model->setSeated(false);
        model->setHasOrdered(false);
        model->setConsuming(false);
        emit model->clientLeft();
    }
}
