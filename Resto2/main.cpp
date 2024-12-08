
#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QIcon>



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/menu.png"));


    MainWindow window;

    window.show();     // Affichez la fenêtre principale
    return a.exec();   // Lancer la boucle d'exécution principale


}
