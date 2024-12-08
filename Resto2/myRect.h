#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QKeyEvent>

class MyRect : public QGraphicsRectItem {
public:
    MyRect() = default;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MYRECT_H
