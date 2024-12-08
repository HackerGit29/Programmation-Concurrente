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


// Retourne la première table disponible qui correspond à la taille du groupe

Table* TableController::findAvailableTable(int groupSize) {
    for (Table* table : tables) {
        if (!table->isOccupied() && table->getCapacity() >= groupSize) {
            return table; // Retourne la première table disponible
        }
    }
    return nullptr; // Aucune table disponible
}

QVector<Table*> TableController::getTables() const {
    return tables;
}
