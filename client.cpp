#include "client.h"
#include <QGraphicsTextItem>
#include <QFont>

Client::Client(const QString &imagePath, int id, QObject *parent)
    : QObject(parent), graphicsItem(new QGraphicsPixmapItem(QPixmap(imagePath))), id(id), orderPopup(nullptr)
{
    graphicsItem->setZValue(1);
}

Client::~Client()
{
    delete graphicsItem;
    if (orderPopup) {
        delete orderPopup;
    }
}

void Client::setPosition(int x, int y, double scale)
{
    if (graphicsItem) {
        graphicsItem->setPos(x, y);
        graphicsItem->setScale(scale / 100.0);
    }
}

void Client::orderDish(const QString &dish)
{
    Q_UNUSED(dish);
}

QGraphicsPixmapItem* Client::getGraphicsItem() const
{
    return graphicsItem;
}

int Client::getId() const
{
    return id;
}

void Client::showOrderPopup(const QString &message, QGraphicsScene *scene)
{
    if (orderPopup) {
        scene->removeItem(orderPopup);
        delete orderPopup;
    }

    orderPopup = new QGraphicsTextItem(message);
    orderPopup->setFont(QFont("Arial", 12));
    orderPopup->setPos(graphicsItem->pos().x(), graphicsItem->pos().y() - 30);
    orderPopup->setZValue(2);
    scene->addItem(orderPopup);
}
