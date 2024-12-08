#include "MyRect.h"
#include <QKeyEvent>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDir>

void MyRect::keyPressEvent(QKeyEvent *event) {
    // Déplacement du rectangle en fonction de la touche pressée
    if (event->key() == Qt::Key_Left) {
        setPos(x() - 10, y());
    } else if (event->key() == Qt::Key_Right) {
        setPos(x() + 10, y());
    } else if (event->key() == Qt::Key_Up) {
        setPos(x(), y() - 10);
    } else if (event->key() == Qt::Key_Down) {
        setPos(x(), y() + 10);
    }

    // Récupérer les vraies coordonnées dans la scène
    QPointF scenePosition = scenePos();

    // Chemin du fichier
    QDir dir(QCoreApplication::applicationDirPath() + "/position");
    if (!dir.exists()) {
        dir.mkpath("."); // Crée le dossier s'il n'existe pas
    }
    QFile file(QCoreApplication::applicationDirPath() + "/position/positions.txt");

    // Ouvrir le fichier en mode ajout pour écrire la nouvelle position
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Nouvelle position dans la scène: (" << scenePosition.x() << ", " << scenePosition.y() << ")\n";
        out.flush(); // Vide explicitement le tampon dans le fichier
        file.close();
    } else {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier positions.txt pour écrire";
    }
}
