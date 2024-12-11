#include "menucontroller.h"
#include "ingredient.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>


MenuController::MenuController(Order *orderModel, const QList<Client*> &clients, QObject *parent)
    : QObject(parent), orderModel(orderModel), clients(clients) {}

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

void MenuController::createOrderFromMenu(QListWidget *menuListWidget, int clientId, int tableId) {
    QListWidgetItem *selectedItem = menuListWidget->currentItem();
    if (!selectedItem) {
        qDebug() << "Aucun élément de menu sélectionné.";
        return;
    }

    QString dishName = selectedItem->text();
    int quantity = QRandomGenerator::global()->bounded(1, 8);


    QList<OrderItem> items = {{dishName, quantity}};
    orderModel->addOrder(clientId, tableId, items);

    // Mettre à jour la quantité des ingrédients
    updateIngredientQuantities(dishName, quantity);
}

void MenuController::updateIngredientQuantities(const QString &dishName, int quantity) {
    QSqlQuery query;
    query.prepare("SELECT i.ingredient_id, mi.quantity FROM menu_ingredients mi JOIN menu m ON mi.menu_id = m.menu_id JOIN ingredients i ON mi.ingredient_id = i.ingredient_id WHERE m.nom = :dishName");
    query.bindValue(":dishName", dishName);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des ingrédients du menu:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int ingredientId = query.value(0).toInt();
        int ingredientQuantity = query.value(1).toInt();
        Ingredient::updateQuantity(ingredientId, ingredientQuantity * quantity);
    }
}
