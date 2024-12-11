#include "Equipement.h"

Equipement::Equipement(const QString& nom, const QString& imagePath)
    : nom(nom), imagePath(imagePath), pixmapItem(new QGraphicsPixmapItem(QPixmap(imagePath))) {}

QGraphicsPixmapItem* Equipement::getGraphicsItem() const {
    return pixmapItem;
}

void Equipement::setPosition(int x, int y) {
    pixmapItem->setPos(x, y);
}
