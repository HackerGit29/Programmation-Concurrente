#include "order.h"

Order::Order(int clientId, const QVector<QString> &dishes)
    : clientId(clientId), dishes(dishes) {}

// Getters
int Order::getClientId() const {
    return clientId;
}

QVector<QString> Order::getDishes() const {
    return dishes;
}

// Setters
void Order::setDishes(const QVector<QString> &dishes) {
    this->dishes = dishes;
}
