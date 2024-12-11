#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "clientcontroller.h"
#include "chaisecontroller.h"
#include "ordercontroller.h"
#include "tablecontroller.h"
#include "fridgecontroller.h"
#include "lavecontroller.h"
#include "staff.h"
#include "plongeurcontroller.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <GraphicsPixmapItemWithProperties.h>
#include <QMessageBox>
#include <QTimeLine>
#include <QList>
#include <QSqlDatabase>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startSimulation();       // Démarre la simulation
    void pauseSimulation();       // Met la simulation en pause
    void stopSimulation();        // Arrête complètement la simulation
    void updateTime();            // Met à jour le temps de la simulation
    void accelSimulation();       // Accélère ou revient à la vitesse normale de la simulation
    void updateIngredients();     // pour update la table ingrédients une seule fois
    // void updateUI();





private:

    Staff *chefItem;    // Objet représentant le chef
    Staff *server;  // Objet représentant le serveur
    Staff* plongeur;

    void setupStaff();
    void movePlongeur();
    void setupPlongeurMovement();
    void moveChefToNextTask();
    void moveChefBetweenComptoirAndFrigo();
    void setupChefMovement();
    void moveChefInKitchen();
    void moveServerToClient(Client *client); // Déplacer le serveur vers un client
    void moveClientToTable(Client *client, Table *table);

    Ui::MainWindow *ui;
    bool isRunning;                           // Indique si la simulation est en cours
    int simulationTime;                       // Temps écoulé dans la simulation (en secondes)
    int timeScale;                            // Facteur de vitesse (1x ou 2x)

    QGraphicsScene *diningScene;              // Scène pour la salle à manger
    QGraphicsScene *kitchenScene;             // Scène pour la cuisine
    GraphicsPixmapItemWithProperties *chef;
    // GraphicsPixmapItemWithProperties *chef;

    QList<QPointF> chefTargets; // Liste des positions cibles
    int currentTaskIndex;

    QTimer *timer;                            // Timer pour gérer la simulation
    QTimer *dbUpdateTimer;                    // Update du stock
    QFile logFile;                            // Fichier pour les logs

    QList<QGraphicsPixmapItem *> clientItems; // Liste des clients (objets graphiques)
    QList<QTimeLine *> clientTimelines;       // Liste des timelines pour les animations
    ClientController clientController;
    ChaiseController chaiseController;
    OrderController orderController;
    TableController tableController;
    FridgeController fridgeController;
    LaveController laveController;
    QSqlDatabase   db;
    // Ingredients *ingredients;

    bool connectToDatabase();
    void loadMenuData();
    void loadStockInfo();
    void loadInventoryData();
    void logMessage(const QString &message);  // Écrit un message dans le fichier de log
    void showPopup(const QString &message, QGraphicsItem *client); // Affiche un popup au-dessus d'un client
    void  updateDatabase();


protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // MAINWINDOW_H
