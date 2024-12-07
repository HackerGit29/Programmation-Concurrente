#include "fridgecontroller.h"

FridgeController::FridgeController(QObject *parent) : QObject(parent) {}

void FridgeController::addFridge(Fridge *fridge) {
    getFridges().append(fridge);
}

Fridge *FridgeController::findFidgeById(int fridgeId) {
    for (Fridge *fridge : fridge) {
        if (fridge->getId() == fridgeId) {
            return fridge;
        }
    }
    return nullptr;
}

QVector<Fridge*> FridgeController::getFridges() const {
    return fridge;
}
