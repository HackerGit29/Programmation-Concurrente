#include "table.h"

#include <QToolTip>


Table::Table(int id, int capacity, const QString &imagePath, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(QPixmap(imagePath)),id(id), capacity(capacity), occupied(false) {

    setScale(0.1); // Ajustez l'échelle selon vos besoins

    setAcceptHoverEvents(true);

    textItem = new QGraphicsTextItem(QString("Table %1\nCapacité: %2").arg(id).arg(capacity), this);
    textItem->setDefaultTextColor(Qt::white);
    textItem->setPos(0, -20);
}

Table::~Table() {}

void Table::setPosition(int x, int y) {
    setPos(x, y);
}

void Table::setOccupied(bool occupied) {
    this->occupied = occupied;
    setOpacity(occupied ? 0.5 : 1.0);
}

bool Table::isOccupied() const {
    return occupied;
}

int Table::getCapacity() const {
    return capacity;
}

int Table::getId() const {
    return id;
}


QGraphicsPixmapItem* Table::getGraphicsItem() {
    return this;
}


const QGraphicsPixmapItem* Table::getGraphicsItem() const {
    return this;
}

QGraphicsTextItem* Table::getTextItem() const {
    return textItem;
}

void Table::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QToolTip::showText(event->screenPos(), QString("Capacité: %1\nOccupée: %2").arg(capacity).arg(occupied ? "Oui" : "Non"));
}

void Table::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QToolTip::hideText();
}
