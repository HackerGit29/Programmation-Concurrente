#include "chaisecontroller.h"
#include <QPixmap>
#include <QPainter>

void ChaiseController::addChaise(const Chaise &chaise) {
    chaises.append(chaise);
}

void ChaiseController::drawChaises(QPainter &painter) const {
    for (const Chaise &chaise : chaises) {
        QPixmap pixmap(chaise.getImagePath());
        painter.drawPixmap(chaise.getX(), chaise.getY(), pixmap.width(), pixmap.height(), pixmap);
    }
}
