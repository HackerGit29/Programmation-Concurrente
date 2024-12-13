#include "alertes.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>

Alertes::Alertes(QObject *parent) : QObject(parent) {}

void Alertes::showAlerts(QDialog *dialog, const QList<Client*> &clients, const QVector<Table*> &tables, const QVector<Employee*> &employees) {
    QVBoxLayout *layout = new QVBoxLayout(dialog);

    // Récupérer les widgets de l'UI
    QLabel *clientsCardValue = dialog->findChild<QLabel*>("clientsCardValue");
    QLabel *tablesCardValue = dialog->findChild<QLabel*>("tablesCardValue");
    QLabel *staffCardValue = dialog->findChild<QLabel*>("staffCardValue");
    QTableView *ingredientsTableView = dialog->findChild<QTableView*>("ingredientsTableView");
    QTableView *alertsListWidget = dialog->findChild<QTableView*>("alertsListWidget");

    // Mettre à jour les cartes
    updateClientsCard(clientsCardValue, clients);
    updateTablesCard(tablesCardValue, tables);
    updateStaffCard(staffCardValue, employees);
    updateIngredientsTable(ingredientsTableView);
    updateAlertsList(alertsListWidget, clients, tables);

    dialog->setLayout(layout);
    dialog->exec();
}

void Alertes::updateClientsCard(QLabel *label, const QList<Client*> &clients) {
    int seatedClients = 0;
    for (const Client* client : clients) {
        if (client->getIsSeated()) {
            seatedClients++;
        }
    }
    label->setText(QString::number(seatedClients));
}

void Alertes::updateTablesCard(QLabel *label, const QVector<Table*> &tables) {
    int totalTables = tables.size();
    int occupiedTables = 0;
    for (const Table* table : tables) {
        if (table->isOccupied()) {
            occupiedTables++;
        }
    }
    label->setText(QString("%1/%2").arg(occupiedTables).arg(totalTables));
}

void Alertes::updateStaffCard(QLabel *label, const QVector<Employee*> &employees) {
    int staffCount = employees.size();
    label->setText(QString::number(staffCount));
}

void Alertes::updateIngredientsTable(QTableView *tableView) {
    QStandardItemModel *model = new QStandardItemModel(tableView);
    model->setHorizontalHeaderLabels({"Ingrédient", "Quantité"});

    QList<Ingredient> ingredients = Ingredient::getAllIngredients();

    for (const auto &item : ingredients) {
        QStandardItem *ingredientItem = new QStandardItem(item.getName());
        QStandardItem *quantityItem = new QStandardItem(QString::number(item.getQuantity()));
        model->appendRow({ingredientItem, quantityItem});
    }

    tableView->setModel(model);
}

void Alertes::updateAlertsList(QTableView *tableView, const QList<Client*> &clients, const QVector<Table*> &tables) {
    QStandardItemModel *model = new QStandardItemModel(tableView);
    model->setHorizontalHeaderLabels({"Type d'alerte", "Description"});

    // Exemple d'alertes
    if (clients.isEmpty()) {
        QStandardItem *item1 = new QStandardItem("Alerte");
        QStandardItem *item2 = new QStandardItem("Aucun client assis");
        model->appendRow({item1, item2});
    }

    for (const Table* table : tables) {
        if (!table->isOccupied()) {
            QStandardItem *item1 = new QStandardItem("Alerte");
            QStandardItem *item2 = new QStandardItem(QString("Table %1 vide").arg(table->getId()));
            model->appendRow({item1, item2});
        }
    }

    QList<Ingredient> ingredients = Ingredient::getAllIngredients();

    for (const auto &item : ingredients) {
        if (item.getQuantity() < 5) {
            QStandardItem *item1 = new QStandardItem("Alerte");
            QStandardItem *item2 = new QStandardItem(QString("Ingrédient %1 en quantité insuffisante").arg(item.getName()));
            model->appendRow({item1, item2});
        }
    }

    tableView->setModel(model);
}
