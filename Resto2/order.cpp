#include "order.h"

#include <QString>



Order::Order(QObject *parent) : QObject(parent) {}

void Order::addOrder(int clientId, int tableId, const QList<OrderItem> &items) {
    orders.append({clientId, tableId, items});
    emit orderAdded(clientId, tableId);
}

void Order::removeOrder(int clientId) {
    auto it = std::remove_if(orders.begin(), orders.end(),
                             [clientId](const OrderDetails &order) {
                                 return order.clientId == clientId;
                             });
    if (it != orders.end()) {
        orders.erase(it, orders.end());
        emit orderRemoved(clientId);
    }
}

QList<OrderItem> Order::getItemsForClient(int clientId) const {
    for (const auto &order : orders) {
        if (order.clientId == clientId) {
            return order.items;
        }
    }
    return {}; // Retourne une liste vide si aucun client ne correspond.
}

QList<OrderDetails> Order::getOrders() const {
    return orders;
}
