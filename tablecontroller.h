#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include "table.h"
#include <QVector>
//#include <QMutex>

class TableController {
public:
    void addTable(Table *table);
    void drawTables(QGraphicsScene *scene) const;
    Table *findTableById(int tableId);


private:
    QVector<Table*> tables;
 //   mutable QMutex mutex; // Mutex for thread safety
};

#endif // TABLECONTROLLER_H

