#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #include "clientcontroller.h"
#include "alertes.h"
#include "gameSettings.h"
#include "stockwindow.h"
#include "tablecontroller.h"
#include "clientcontroller.h"
#include "employeecontroller.h"
#include "order.h"
#include "menucontroller.h"
#include "controldialog.h"
#include "client.h"
#include "fridgecontroller.h"
#include "lavecontroller.h"
#include "staff.h"
#include "plongeurcontroller.h"
#include <QKeyEvent>
#include <QShortcut>
#include <QTcpSocket>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>
#include <GraphicsPixmapItemWithProperties.h>
#include <QMessageBox>
#include <QTimeLine>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>
#include <QGraphicsEllipseItem>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QThreadPool>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

signals:




private slots:
    // void updateTime();
    void startSimulation();
    void pauseSimulation();
    void stopSimulation();
    void updateTime();            // Met à jour le temps de la simulation
    void accelSimulation();
    void updateStockLevelsProgressBar();
    void updateTableSeatsProgressBar();
    void onOrderAdded(int clientId, int tableId);
    void onOrderRemoved(int clientId);
    void handleSocketReadyRead();
    void handleClientCommand(int clientId, int tableId, const QList<OrderItem> &items);
    void serveOrder(int clientId);
    void on_paramButton_clicked();
    void on_livraisonButton_clicked();
    void on_alertButton_clicked();

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
    QSqlDatabase db;
    QTimer *timer;
    QTimer *stockTimer;
    bool isRunning;
    int simulationTime;
    int timeScale;
    QGraphicsScene *diningScene;
    QGraphicsScene *kitchenScene;  
    QGraphicsEllipseItem *diningItem;
    QGraphicsEllipseItem *kitchenItem;
    GraphicsPixmapItemWithProperties *chef;
    QPropertyAnimation *diningAnimation;
    QPropertyAnimation *kitchenAnimation;
    QFile logFile;
    GameSettings *dialog;
    stockWindow  *stockwindow;
    ControlDialog *control;
    //QList<QGraphicsPixmapItem *> clientItems; // Liste des clients (objets graphiques)
    QList<QTimeLine *> clientTimelines;       // Liste des timelines pour les animations
    QList<Client*> clients;
    ClientController clientController;
    Order *orderModel;
    TableController tableController;
    EmployeeController employeeController;
    FridgeController fridgeController;
    LaveController laveController;
    MenuController *menuController;
    QGraphicsEllipseItem* animatedCircle = nullptr;
    QTcpSocket *socket;
    Alertes *alertes;
    QThreadPool *threadPool;
    // QList<QThread*> clientTimelines;
    QList<Client*> clientItems;

    QList<QPointF> chefTargets; // Liste des positions cibles
    int currentTaskIndex;




    // QPointF getTablePosition(int tableId);
    void createOrder(int clientId, int tableId);
    void markOrderReady(int tableId);

    // QMediaPlayer *mediaPlayer;
    // QAudioOutput *audioOutput;


    bool connectToDatabase();
    void loadMenuData();
    void loadStockInfo();
    void loadInventoryData();
    void logMessage(const QString &message);
    void openSettingsDialog();
    void updateCustomerInfo();
    // void updateTableInfo();
    void simulateClientActivity(Client* client, Table* table);
    void showAlerts();



};

#endif // MAINWINDOW_H
