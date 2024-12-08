#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #include "clientcontroller.h"
#include "tablecontroller.h"
#include "clientcontroller.h"
#include "employeecontroller.h"
#include "order.h"
#include "menucontroller.h"
#include "client.h"
#include <QKeyEvent>
#include <QShortcut>
#include <QTcpSocket>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
// #include <QMediaPlayer>
// #include <QAudioOutput>
#include <QPropertyAnimation>
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
    void updateTime();
    void startSimulation();
    void pauseSimulation();
    void stopSimulation();
    void accelSimulation();
    void updateStockLevelsProgressBar();
    void updateTableSeatsProgressBar();
    void onOrderAdded(int clientId, int tableId);
    void onOrderRemoved(int clientId);
    void handleSocketReadyRead();
    void handleClientCommand(int clientId, int tableId, const QList<OrderItem> &items);
    void serveOrder(int clientId);


private:
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
    QPropertyAnimation *diningAnimation;
    QPropertyAnimation *kitchenAnimation;
    QFile logFile;

    QList<QGraphicsPixmapItem *> clientItems; // Liste des clients (objets graphiques)
    QList<QTimeLine *> clientTimelines;       // Liste des timelines pour les animations
    QList<Client*> clients;
    ClientController clientController;
    Order *orderModel;
    TableController tableController;
    EmployeeController employeeController;
    MenuController *menuController;
    QGraphicsEllipseItem* animatedCircle = nullptr;
    QTcpSocket *socket;
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


};

#endif // MAINWINDOW_H
