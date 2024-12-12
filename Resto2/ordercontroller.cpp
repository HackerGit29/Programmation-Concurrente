#include "ordercontroller.h"

void OrderController::addOrder(const Order &order) {
    orders.append(order);
}

QVector<Order> OrderController::getOrdersForClient(int clientId) const {
    QVector<Order> clientOrders;
    for (const Order &order : orders) {
        if (order.getClientId() == clientId) {
            clientOrders.append(order);
        }
    }
    return clientOrders;
}
