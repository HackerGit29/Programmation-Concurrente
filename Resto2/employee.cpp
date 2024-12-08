#include "employee.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QToolTip>

Employee::Employee(int id, const QString &name, const QString &role, const QString &imagePath, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(QPixmap(imagePath)), id(id), name(name), role(role) {
    setScale(0.5); // Ajustez l'échelle selon vos besoins
    textItem = new QGraphicsTextItem(name + "\n" + role, this);
    textItem->setPos(boundingRect().center());
    setAcceptHoverEvents(true); // Activer les événements de survol
}

Employee::~Employee() {
    delete textItem;
}

void Employee::setPosition(int x, int y) {
    setPos(x, y);
}

int Employee::getId() const {
    return id;
}

QString Employee::getName() const {
    return name;
}

QString Employee::getRole() const {
    return role;
}

QGraphicsPixmapItem* Employee::getGraphicsItem() {
    return this;
}

const QGraphicsPixmapItem* Employee::getGraphicsItem() const {
    return this;
}

QGraphicsTextItem* Employee::getTextItem() const {
    return textItem;
}

void Employee::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QToolTip::showText(event->screenPos(), QString("Nom: %1\nRole: %2").arg(name).arg(role));
}

void Employee::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QToolTip::hideText();
}
