#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneHoverEvent>

class Employee : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Employee(int id, const QString &name, const QString &role, const QString &imagePath, QObject *parent = nullptr);
    ~Employee();

    void setPosition(int x, int y);
    int getId() const;
    QString getName() const;
    QString getRole() const;
    QGraphicsPixmapItem* getGraphicsItem();
    const QGraphicsPixmapItem* getGraphicsItem() const;
    QGraphicsTextItem* getTextItem() const;



protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    int id;
    QString name;
    QString role;
    QGraphicsTextItem *textItem;
};

#endif // EMPLOYEE_H
