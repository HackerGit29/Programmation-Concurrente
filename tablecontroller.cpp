#include "tablecontroller.h"
//#include <QMutexLocker>

void TableController::addTable(Table *table) {
   // QMutexLocker locker(&mutex); // Lock the mutex
    tables.append(table);
}


void TableController::drawTables(QGraphicsScene *scene) const {
  //  QMutexLocker locker(&mutex); // Lock the mutex
    for (Table *table : tables) {
        scene->addItem(table->getGraphicsItem());
    }
}


Table *TableController::findTableById(int tableId) {
    for (Table *table : tables) {
        if (table->getId() == tableId) {
            return table;
        }
    }
    return nullptr;
}

