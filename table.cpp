#include "table.h"
#include <QPixmap>

Table::Table(const QString &imagePath, int id, QObject *parent)
    : QObject(parent), graphicsItem (new QGraphicsPixmapItem(QPixmap(imagePath))), id(id)
{
    graphicsItem->setZValue(1);
}

Table::~Table() {
    delete graphicsItem;
}


void Table::setPosition(int x, int y, double scale) {


if (graphicsItem) {
   // QMutexLocker locker(&mutex); // Lock the mutex
    graphicsItem->setPos(x, y);
    graphicsItem->setScale(scale/100.0);

    }
   
}

QGraphicsPixmapItem* Table::getGraphicsItem() const
{
    return graphicsItem;
}


int Table::getId() const {
    return id;
}
