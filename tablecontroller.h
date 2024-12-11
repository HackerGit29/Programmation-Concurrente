#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include <QVector>
#include "table.h"

class TableController : public QObject {
    Q_OBJECT

public:
    TableController(QObject *parent = nullptr);
    void addTable(Table *table);
    Table *findTableById(int tableId);
    QVector<Table*> getTables() const;

private:
    QVector<Table*> tables; // Liste des tables dans le restaurant
};

#endif // TABLECONTROLLER_H
