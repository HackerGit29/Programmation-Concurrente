#ifndef LAVECONTROLLER_H
#define LAVECONTROLLER_H

#include <QVector>
#include "lave.h"

class LaveController : public QObject {
    Q_OBJECT

public:
    LaveController(QObject *parent = nullptr);
    void addLave(Lave *lave);
    Lave *findLaveById(int laveId);
    QVector<Lave*> getLaves() const;

private:
    QVector<Lave*> lave; // Liste des tables dans le restaurant
};

#endif // LAVECONTROLLER_H
