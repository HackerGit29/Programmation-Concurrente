#ifndef PLONGEUR_H
#define PLONGEUR_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class Plongeur : public QObject {
    Q_OBJECT

public:
    Plongeur(const QString &imagePath, int id, QObject *parent = nullptr);
    ~Plongeur();

    void setPosition(int x, int y, double scale);
    void orderDish(const QString &dish);
    QGraphicsPixmapItem* getGraphicsItem() const;
    int getId() const;
    void showOrderPopup(const QString &message, QGraphicsScene *scene);

private:
    QGraphicsPixmapItem *graphicsItem;
    int id;
    QGraphicsTextItem *orderPopup;
};

#endif // PLONGEUR_H
