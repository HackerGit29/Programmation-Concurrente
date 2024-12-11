#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <QObject>
#include <QList>
#include <QListWidget>
#include "menu.h"
#include "order.h"
#include "client.h"

class MenuController : public QObject {
    Q_OBJECT

public:
    MenuController(Order *orderModel, const QList<Client*> &clients, QObject *parent = nullptr);

    QList<Menu> getAllMenus();
    void createOrderFromMenu(QListWidget *menuListWidget, int clientId, int tableId);
    void updateIngredientQuantities(const QString &dishName, int quantity);


private:

    Order *orderModel;
    QList<Client*> clients;
};

#endif // MENUCONTROLLER_H
