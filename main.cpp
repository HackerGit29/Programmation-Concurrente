
#include <QApplication>
#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow window;

    window.show();     // Affichez la fenêtre principale
    return a.exec();   // Lancer la boucle d'exécution principale


}
