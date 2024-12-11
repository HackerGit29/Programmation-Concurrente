#include "order.h"

#include <QString>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>




Order::Order(QObject *parent) : QObject(parent) {}

void Order::addOrder(int clientId, int tableId, const QList<OrderItem> &items) {
    QSqlQuery query;
    query.prepare("INSERT INTO commandes (client_id, table_id, heure_commande, statut) VALUES (:client_id, :table_id, :heure_commande, :statut)");
    query.bindValue(":client_id", clientId);
    query.bindValue(":table_id", tableId);
    query.bindValue(":heure_commande", QDateTime::currentDateTime());
    query.bindValue(":statut", "En cours");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion de la commande:" << query.lastError().text();
        return;
    }

    int commandeId = query.lastInsertId().toInt();

    for (const OrderItem &item : items) {
        QSqlQuery menuQuery;
        menuQuery.prepare("INSERT INTO menu_ingredients (menu_id, ingredient_id, quantite) VALUES (:menu_id, :ingredient_id, :quantite)");
        menuQuery.bindValue(":menu_id", commandeId);
        menuQuery.bindValue(":ingredient_id", item.first);
        menuQuery.bindValue(":quantite", item.second);

        if (!menuQuery.exec()) {
            qDebug() << "Erreur lors de l'insertion des ingrédients du menu:" << menuQuery.lastError().text();
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
        emit orderRemoved(clientId); // Signaler qu'une commande a été supprimée
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












QList<OrderDetails> Order::getOrders() {
    return orders;
}
