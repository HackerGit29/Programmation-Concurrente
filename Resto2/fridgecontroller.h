#ifndef FRIDGECONTROLLER_H
#define FRIDGECONTROLLER_H

#include <QVector>
#include "fridge.h"

class FridgeController : public QObject {
    Q_OBJECT

public:
    FridgeController(QObject *parent = nullptr);
    void addFridge(Fridge *fridge);
    Fridge *findFidgeById(int fridgeId);
    QVector<Fridge*> getFridges() const;

private:
    QVector<Fridge*> fridge; // Liste des tables dans le restaurant
};

#endif // FRIDGECONTROLLER_H
