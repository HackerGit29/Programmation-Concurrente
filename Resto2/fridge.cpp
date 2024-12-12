#include "fridge.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QToolTip>

Fridge::Fridge(int id, int capacity, const QString &imagePath, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(QPixmap(imagePath)), id(id), capacity(capacity), occupied(false) {
    setScale(1.5); // Ajustez l'échelle selon vos besoins
    textItem = new QGraphicsTextItem(QString::number(capacity), this);
    textItem->setPos(boundingRect().center());
    setAcceptHoverEvents(true); // Activer les événements de survol
}

Fridge::~Fridge() {
    delete textItem;
}

void Fridge::setPosition(int x, int y) {
    setPos(x, y);
}

void Fridge::setOccupied(bool occupied) {
    this->occupied = occupied;
    setOpacity(occupied ? 0.5 : 0.0); // Changer l'opacité pour indiquer l'occupation
}

bool Fridge::isOccupied() const {
    return occupied;
}

int Fridge::getCapacity() const {
    return capacity;
}

int Fridge::getId() const {
    return id;
}

QGraphicsPixmapItem* Fridge::getGraphicsItem() {
    return this;
}

const QGraphicsPixmapItem* Fridge::getGraphicsItem() const {
    return this;
}

QGraphicsTextItem* Fridge::getTextItem() const {
    return textItem;
}

void Fridge::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QToolTip::showText(event->screenPos(), QString("Capacité: %1\nOccupée: %2").arg(capacity).arg(occupied ? "Oui" : "Non"));
}

void Fridge::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QToolTip::hideText();
}
