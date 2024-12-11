#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QVector>

class Order {
public:
    Order(int clientId, const QVector<QString> &dishes);

    // Getters
    int getClientId() const;
    QVector<QString> getDishes() const;

    // Setters
    void setDishes(const QVector<QString> &dishes);

private:
    int clientId;           // Identifiant du client
    QVector<QString> dishes; // Liste des plats commandés
};

#endif // ORDER_H
