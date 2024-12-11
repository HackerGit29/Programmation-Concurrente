#include "tablecontroller.h"

TableController::TableController(QObject *parent) : QObject(parent) {}

void TableController::addTable(Table *table) {
    tables.append(table);
}

Table *TableController::findTableById(int tableId) {
    for (Table *table : tables) {
        if (table->getId() == tableId) {
            return table;
        }
    }
    return nullptr;
}

QVector<Table*> TableController::getTables() const {
    return tables;
}
