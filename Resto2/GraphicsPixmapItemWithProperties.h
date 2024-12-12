#ifndef GRAPHICSPIXMAPITEMWITHPROPERTIES_H
#define GRAPHICSPIXMAPITEMWITHPROPERTIES_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPointF>

class GraphicsPixmapItemWithProperties : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos) // Ajout de la propriété animable

public:
    explicit GraphicsPixmapItemWithProperties(const QPixmap &pixmap, QObject *parent = nullptr)
        : QObject(parent), QGraphicsPixmapItem(pixmap) {}
};
#endif // GRAPHICSPIXMAPITEMWITHPROPERTIES_H
