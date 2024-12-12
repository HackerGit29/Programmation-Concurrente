#include "lavecontroller.h"

LaveController::LaveController(QObject *parent) : QObject(parent) {}

void LaveController::addLave(Lave *lave) {
    getLaves().append(lave);
}

Lave *LaveController::findLaveById(int laveId) {
    for (Lave *lave : lave) {
        if (lave->getId() == laveId) {
            return lave;
        }
    }
    return nullptr;
}

QVector<Lave*> LaveController::getLaves() const {
    return lave;
}
