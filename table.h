#ifndef TABLE_H
#define TABLE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
//#include <QMutex>

class Table : public QObject {
    Q_OBJECT

public:
    Table(const QString &imagePath, int id, QObject *parent = nullptr);
    ~Table();

    void setPosition(int x, int y, double scale);
    QGraphicsPixmapItem* getGraphicsItem() const;
    int getId() const;

private:
    QGraphicsPixmapItem *graphicsItem;
    int id;
  //  mutable QMutex mutex; // Mutex for thread safety
};

#endif // TABLE_H
