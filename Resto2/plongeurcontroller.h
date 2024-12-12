// plongeurcontroller.h
#ifndef PLONGEURCONTROLLER_H
#define PLONGEURCONTROLLER_H

#include <QVector>
#include "plongeur.h"

class PlongeurController {
public:
    void addPlongeur(Plongeur *plongeur);
    void movePlongeur(int plongeurId, int x, int y, double scale = 100.0);
    Plongeur *findPlongeurById(int plongeurId);

private:
    QVector<Plongeur*> plongeurs; // Liste des plongeurs dans la salle
};

#endif // PLONGEURCONTROLLER_H
