#ifndef LAVE_H
#define LAVE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneHoverEvent>

class Lave : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Lave(int id, int capacity, const QString &imagePath, QObject *parent = nullptr);
    ~Lave();

    void setPosition(int x, int y);
    void setOccupied(bool occupied);
    bool isOccupied() const;
    int getCapacity() const;
    int getId() const;
    QGraphicsPixmapItem* getGraphicsItem();
    const QGraphicsPixmapItem* getGraphicsItem() const;
    QGraphicsTextItem* getTextItem() const;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    int id;
    int capacity;
    bool occupied;
    QGraphicsTextItem *textItem;
};

#endif // LAVE_H
