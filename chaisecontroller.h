#ifndef CHAISECONTROLLER_H
#define CHAISECONTROLLER_H

#include <QVector>
#include <QPainter>
#include "chaise.h"

class ChaiseController {
public:
    void addChaise(const Chaise &chaise);
    void drawChaises(QPainter &painter) const;

private:
    QVector<Chaise> chaises; // Liste de chaises
};

#endif // CHAISECONTROLLER_H
