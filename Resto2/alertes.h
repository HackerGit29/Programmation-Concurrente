#ifndef ALERTES_H
#define ALERTES_H

#include <QObject>
#include <QString>
#include <QList>
#include <QDialog>
#include <QTableView>
#include <QLabel>

#include "client.h"
#include "table.h"
#include "employee.h"
#include "ingredient.h"

class Alertes : public QObject {
    Q_OBJECT

public:
    Alertes(QObject *parent = nullptr);

    void showAlerts(QDialog *dialog, const QList<Client*> &clients, const QVector<Table*> &tables, const QVector<Employee*> &employees);
    void updateAlertsList(QTableView *tableView, const QList<Client*> &clients, const QVector<Table*> &tables);

private:
    void updateClientsCard(QLabel *label, const QList<Client*> &clients);
    void updateTablesCard(QLabel *label, const QVector<Table*> &tables);
    void updateStaffCard(QLabel *label, const QVector<Employee*> &employees);
    void updateIngredientsTable(QTableView *tableView);
};

#endif // ALERTES_H
