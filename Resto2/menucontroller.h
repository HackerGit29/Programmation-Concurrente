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
    explicit MenuController(Order *orderModel, const QList<Client*> &clients, QObject *parent = nullptr);

    void setupRefreshTimer(QListWidget *menuListWidget, QListWidget *orderListWidget);
    void refreshOrderList(QListWidget *orderListWidget);
    void createOrderFromMenu(QListWidget *menuListWidget, int clientId, int tableId);

    QList<Menu> getAllMenus();
    int getGroupSize(int clientId) const;


private:
    Order *orderModel;
    QList<Client*> clients;

};

#endif // MENUCONTROLLER_H
