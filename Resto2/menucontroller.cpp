#include "menucontroller.h"
#include "client.h"
#include <QTimer>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

MenuController::MenuController(Order *orderModel, const QList<Client*> &clients, QObject *parent)
    : QObject(parent), orderModel(orderModel), clients(clients) {}

int MenuController::getGroupSize(int clientId) const {
    for (const Client* client : clients) {  // Parcourir la liste des clients
        if (client->getId() == clientId) {  // Vérifier l'identifiant du client
            return client->getGroupSize();
        }
    }
    return 0;  // Retourne 0 si aucun client ne correspond
}


QList<Menu> MenuController::getAllMenus() {
    QList<Menu> menuList;

    QSqlQuery query("SELECT nom FROM menu");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des menus:" << query.lastError().text();
        return menuList;
    }

    while (query.next()) {
        QString menuName = query.value(0).toString();
        menuList.append(Menu(menuName));
    }

    return menuList;
}

void MenuController::setupRefreshTimer(QListWidget *menuListWidget, QListWidget *orderListWidget) {
    QTimer *refreshTimer = new QTimer(this);

    connect(refreshTimer, &QTimer::timeout, this, [this, menuListWidget]() {
        menuListWidget->clear();
        QList<Menu> menus = getAllMenus();
        for (const Menu &menu : menus) {
            menuListWidget->addItem(menu.getName());
        }
    });

    connect(refreshTimer, &QTimer::timeout, this, [this, orderListWidget]() {
        refreshOrderList(orderListWidget);
    });

    refreshTimer->start(2000); // Rafraîchit toutes les 2 secondes.
}




void MenuController::refreshOrderList(QListWidget *orderListWidget) {
    orderListWidget->clear();

    QList<OrderDetails> allOrders = orderModel->getOrders();

    for (const auto &order : allOrders) {
        QString description = QString("Client %1 - Table %2 (Groupe: %3)\n")
        .arg(order.clientId)
            .arg(order.tableId)
            .arg(getGroupSize(order.clientId));

        for (const auto &item : order.items) {
            description += QString(" - %1 x%2\n")
            .arg(item.first)  // Nom du plat
                .arg(item.second);  // Quantité
        }

        orderListWidget->addItem(description);
    }
}



void MenuController::createOrderFromMenu(QListWidget *menuListWidget, int clientId, int tableId) {
    QListWidgetItem *selectedItem = menuListWidget->currentItem();
    if (!selectedItem) {
        qDebug() << "Aucun élément de menu sélectionné.";
        return;
    }

    QString dishName = selectedItem->text();
    int quantity = 1; // Exemple d'entrée utilisateur.

    QList<OrderItem> items = {{dishName, quantity}};
    orderModel->addOrder(clientId, tableId, items);
}
