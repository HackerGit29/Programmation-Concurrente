#include "plongeurcontroller.h"

void PlongeurController::addPlongeur(Plongeur *plongeur) {
    plongeurs.append(plongeur);
}

void PlongeurController::movePlongeur(int plongeurId, int x, int y, double scale) {
    for (Plongeur *plongeur : plongeurs) {
        if (plongeur->getId() == plongeurId) {
            plongeur->setPosition(x, y, scale);
            break;
        }
    }
}

Plongeur *PlongeurController::findPlongeurById(int plongeurId) {
    for (Plongeur *plongeur : plongeurs) {
        if (plongeur->getId() == plongeurId) {
            return plongeur;
        }
    }
    return nullptr;
}
