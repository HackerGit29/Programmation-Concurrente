#include "lave.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QToolTip>

Lave::Lave(int id, int capacity, const QString &imagePath, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(QPixmap(imagePath)), id(id), capacity(capacity), occupied(false) {
    setScale(1.5); // Ajustez l'échelle selon vos besoins
    textItem = new QGraphicsTextItem(QString::number(capacity), this);
    textItem->setPos(boundingRect().center());
    setAcceptHoverEvents(true); // Activer les événements de survol
}

Lave::~Lave() {
    delete textItem;
}

void Lave::setPosition(int x, int y) {
    setPos(x, y);
}

void Lave::setOccupied(bool occupied) {
    this->occupied = occupied;
    setOpacity(occupied ? 0.5 : 0.0); // Changer l'opacité pour indiquer l'occupation
}

bool Lave::isOccupied() const {
    return occupied;
}

int Lave::getCapacity() const {
    return capacity;
}

int Lave::getId() const {
    return id;
}

QGraphicsPixmapItem* Lave::getGraphicsItem() {
    return this;
}

const QGraphicsPixmapItem* Lave::getGraphicsItem() const {
    return this;
}

QGraphicsTextItem* Lave::getTextItem() const {
    return textItem;
}

void Lave::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QToolTip::showText(event->screenPos(), QString("Capacité: %1\nOccupée: %2").arg(capacity).arg(occupied ? "Oui" : "Non"));
}

void Lave::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QToolTip::hideText();
}
