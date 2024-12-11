#include "table.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QToolTip>

Table::Table(int id, int capacity, const QString &imagePath, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(QPixmap(imagePath)), id(id), capacity(capacity), occupied(false) {
    setScale(1.5); // Ajustez l'échelle selon vos besoins
    textItem = new QGraphicsTextItem(QString::number(capacity), this);
    textItem->setPos(boundingRect().center());
    setAcceptHoverEvents(true); // Activer les événements de survol
}

Table::~Table() {
    delete textItem;
}

void Table::setPosition(int x, int y) {
    setPos(x, y);
}

void Table::setOccupied(bool occupied) {
    this->occupied = occupied;
    setOpacity(occupied ? 0.5 : 0.0); // Changer l'opacité pour indiquer l'occupation
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
