#ifndef ORDERCONTROLLER_H
#define ORDERCONTROLLER_H

#include <QVector>
#include "order.h"

class OrderController {
public:
    void addOrder(const Order &order);
    QVector<Order> getOrdersForClient(int clientId) const;

private:
    QVector<Order> orders; // Liste des commandes
};

#endif // ORDERCONTROLLER_H
