#ifndef ORDER_H
#define ORDER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QPair>

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

    // Nouvelle méthode pour obtenir toutes les commandes
    QList<OrderDetails> getOrders() const;

signals:
    void orderAdded(int clientId, int tableId);
    void orderRemoved(int clientId);

private:
    QList<OrderDetails> orders; // Stockage des commandes.
};

#endif // ORDER_H
