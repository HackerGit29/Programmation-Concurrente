#ifndef ORDER_H
#define ORDER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QPair>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

using OrderItem = QPair<QString, int>; // Nom du plat et quantité.

struct OrderDetails {
    int clientId;
    int tableId;
    QList<OrderItem> items; // Liste des plats avec leurs quantités.
};

class Order : public QObject {
    Q_OBJECT

public:
    explicit Order(QObject *parent = nullptr);

    void addOrder(int clientId, int tableId, const QList<OrderItem> &items);
    void removeOrder(int clientId);
    QList<OrderItem> getItemsForClient(int clientId) const;
    QList<OrderDetails> getOrders() const;

signals:
    void orderAdded(int clientId, int tableId);
    void orderRemoved(int clientId);

private:
    QList<OrderDetails> orders; // Stockage des commandes.
};

#endif // ORDER_H

#include "order.h"

Order::Order(QObject *parent) : QObject(parent) {}

void Order::addOrder(int clientId, int tableId, const QList<OrderItem> &items) {
    QSqlQuery query;

    for (const auto &item : items) {
        query.prepare("INSERT INTO commandes (client_id, table_id, dish_name, quantity) "
                      "VALUES (:client_id, :table_id, :dish_name, :quantity)");
        query.bindValue(":client_id", clientId);
        query.bindValue(":table_id", tableId);
        query.bindValue(":dish_name", item.first);
        query.bindValue(":quantity", item.second);

        if (!query.exec()) {
            qDebug() << "Erreur lors de l'insertion de la commande :" << query.lastError().text();
            return;
        }
    }

    OrderDetails orderDetails;
    orderDetails.clientId = clientId;
    orderDetails.tableId = tableId;
    orderDetails.items = items;
    orders.append(orderDetails);

    emit orderAdded(clientId, tableId);
}

void Order::removeOrder(int clientId) {
    auto it = std::remove_if(orders.begin(), orders.end(), [clientId](const OrderDetails &order) {
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
    return {};
}

QList<OrderDetails> Order::getOrders() const {
    return orders;
}
