#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameSettings.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QTimeLine>
#include <cstdlib>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QPalette>
#include <QRandomGenerator>
#include <QByteArray>


// #include "settings.h"
// #include "stockwindow.h"
// #include "MyRect.h"



// Instancier les fenêtres
// Settings *settingsWindow;
// StockWindow *stockWindow;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer(this)),
    isRunning(false),
    simulationTime(0),
    timeScale(1),
    diningScene(new QGraphicsScene(this)),
    kitchenScene(new QGraphicsScene(this)),
    logFile(QCoreApplication::applicationDirPath() + "/log/simulation.log"),
    // mediaPlayer(new QMediaPlayer(this)),
    // audioOutput(new QAudioOutput(this))
    // settingsDialog(new Settings(this))
    clientController(nullptr),
    orderModel(new Order(this)),
    menuController(nullptr),
    socket(new QTcpSocket(this))

{
    ui->setupUi(this);

    if (connectToDatabase()) {
        loadMenuData();
        loadStockInfo();
        loadInventoryData();
        updateStockLevelsProgressBar();
        updateTableSeatsProgressBar();
        logMessage("Base de données connectée");
    }

    // La sortie Audio
    // mediaPlayer->setAudioOutput(audioOutput);


    // Initialisation du socket
    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 12345); // Port et IP à configurer

    // Connexion des signaux du modèle Order
    connect(orderModel, &Order::orderAdded, this, [this](int clientId, int tableId) {
        QList<OrderItem> items = orderModel->getItemsForClient(clientId);
        handleClientCommand(clientId, tableId, items);
    });

    connect(orderModel, &Order::orderRemoved, this, &MainWindow::serveOrder);


    // Réception des messages du socket
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::handleSocketReadyRead);

   // update l'ui du stock
    QTimer *stockTimer = new QTimer(this);
    // connect(stockTimer, &QTimer::timeout, this, &MainWindow::loadMenuData);
    connect(stockTimer, &QTimer::timeout, this, &MainWindow::loadStockInfo);
    connect(stockTimer, &QTimer::timeout, this, &MainWindow::updateStockLevelsProgressBar);
    connect(stockTimer, &QTimer::timeout, this, &MainWindow::updateTableSeatsProgressBar);
    connect(stockTimer, &QTimer::timeout, this, &MainWindow::loadInventoryData);
    connect(stockTimer, &QTimer::timeout, this, &MainWindow::loadMenuData);
    connect(stockTimer, &QTimer::timeout, this, &MainWindow::updateCustomerInfo);
    // connect(stockTimer, &QTimer::timeout, this, &MainWindow::updateTableInfo);


    stockTimer->start(2000); // Rafraîchissement toutes les 2 secondes

    // controller du menu pour l'affichage sur l'écran
    menuController->setupRefreshTimer(ui->menuListWidget, ui->orderList);

    // connect(stockTimer, &QTimer::timeout, this, [this]() {
    //     qDebug() << "Mise à jour de l'ui activée !";
    //     updateStockLevelsProgressBar();
    // });


    // Configuration des scènes
    ui->diningAreaView->setScene(diningScene);
    ui->kitchenAreaView->setScene(kitchenScene);



    // Connexion des boutons

    connect(ui->stratButton, &QPushButton::clicked, this, &MainWindow::startSimulation);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::pauseSimulation);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopSimulation);
    connect(ui->accelButton, &QPushButton::clicked, this, &MainWindow::accelSimulation);
 //   connect(ui->livraisonButton, &QPushButton::clicked, this, &MainWindow::openStockManagement);
//connect(ui->paramButton, &QPushButton::clicked, this, &MainWindow::openSettings);
  //  connect(settingsDialog->getApplyButton(), &QPushButton::clicked, this, &MainWindow::applySettings);

    // Nettoyer la liste au démarrage
    if (ui->orderList) {
        ui->orderList->clear();
    }






    // Configuration du timer
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);

    // Configuration du fichier log
    QDir logDir(QCoreApplication::applicationDirPath() + "/log");
    if (!logDir.exists()) {
        logDir.mkpath(".");
    }

    if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier de log !";
    } else {
        logMessage("Application démarrée");
    }
}

bool MainWindow::connectToDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/database/restaurant.db");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la BD !:" << db.lastError().text();
        return false;
    }
    return true;
}



void MainWindow::loadMenuData() {
    QSqlQuery query("SELECT nom FROM menu");

    if (!query.exec()) {
        qDebug() << "Failed to retrieve data from the menu table:" << query.lastError().text();
        return;
    }

    ui->menuListWidget->clear();

    while (query.next()) {
        QString menuName = query.value(0).toString();
        QListWidgetItem *item = new QListWidgetItem(menuName, ui->menuListWidget);
        ui->menuListWidget->addItem(item);
    }
}


void MainWindow::loadStockInfo() {
    QSqlQuery query("SELECT nom, quantite FROM ingredients");

    if (!query.exec()) {
        qDebug() << "Les informations du stock d'ingrédients ne sont pas chargées" << query.lastError().text();
        return;
    }

    QString html = R"(
        <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">
        <html><head><meta name="qrichtext" content="1" /><meta charset="utf-8" />
        <style type="text/css">
            p, li { white-space: pre-wrap; }
            hr { height: 1px; border-width: 0; }
            li.unchecked::marker { content: "\2610"; }
            li.checked::marker { content: "\2612"; }
        </style></head><body style=" font-family:'Segoe UI'; font-size:12px; font-weight:400; font-style:normal;">
        <p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;"><span style=" font-family:'MS Shell Dlg 2'; font-size:8.25pt;">Niveaux de stock:</span>
        </p>
    )";

    while (query.next()) {
        QString ingredientName = query.value(0).toString();
        int quantity = query.value(1).toInt();

        html += QString(R"(
        <p style="margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">
            <span style="font-family:'MS Shell Dlg 2'; font-size:8.25pt;">%1 (%2)</span>
        </p>
    )").arg(ingredientName).arg(quantity);
    }

    html += R"(
        </body></html>
    )";

    ui->stockInfoTextBrowser->setHtml(html);
}

void MainWindow::loadInventoryData() {
    QSqlQuery query("SELECT nom_item, quantite FROM inventaire");

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des données de l'inventaire:" << query.lastError().text();
        return;
    }

    QString html = R"(
            <p> Inventaire: </p>
    )";

    while (query.next()) {
        QString itemName = query.value(0).toString();
        int quantity = query.value(1).toInt();

        html += QString(R"(
            <p  %1 (%2) </p>
        )").arg(itemName).arg(quantity);
    }

    html += R"(
        </body>
        </html>
    )";

    // Afficher le HTML dans le widget tableInfoTextBrowser
    ui->tableInfoTextBrowser->setHtml(html);

   // Ajouter des tables

    Table *table1 = new Table(1, 4, ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/cercle_2.png");
    table1->setPosition(200, 0);
    tableController.addTable(table1);
    diningScene->addItem(table1->getGraphicsItem());

    Table *table4 = new Table(4, 8, ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/cercle.png");
    table4->setPosition(150, 0);
    tableController.addTable(table4);
    diningScene->addItem(table4->getGraphicsItem());

    // Table *table5 = new Table(5, 4, ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/cercle.png");
    // table5->setPosition(0, 300);
    // tableController.addTable(table5);
    // diningScene->addItem(table5->getGraphicsItem());

    // Table *table6 = new Table(6, 8, ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/table_1.png");
    // table1->setPosition(160, 200);
    // tableController.addTable(table6);
    // diningScene->addItem(table6->getGraphicsItem());

    // Table *table7 = new Table(7, 8, ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/table_1.png");
    // table7->setPosition(260, 160);
    // tableController.addTable(table7);
    // diningScene->addItem(table7->getGraphicsItem());

    // Table *table8 = new Table(8, 8, ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/table_1.png");
    // table8->setPosition(310, 160);
    // tableController.addTable(table8);
    // diningScene->addItem(table8->getGraphicsItem());

    // Table *table2 = new Table(2, 8, ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/table_1.png");
    // table2->setPosition(60, 160);
    // tableController.addTable(table2);
    // diningScene->addItem(table2->getGraphicsItem());

    // Table *table3 = new Table(3, 8, ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/table_1.png");
    // table3->setPosition(310, 160);
    // tableController.addTable(table3);
    // diningScene->addItem(table3->getGraphicsItem());

    // // Ajouter des employés
    // Employee *maitreHotel = new Employee(1, "Maxim", "Maître d'Hôtel", ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/maitre.png");
    // maitreHotel->setPosition(50, 50);
    // employeeController.addEmployee(maitreHotel);
    // diningScene->addItem(maitreHotel->getGraphicsItem());

    // Employee *chefDeRang = new Employee(2, "Daniel", "Chef de Rang", ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/rang.png");
    // chefDeRang->setPosition(100, 50);
    // employeeController.addEmployee(chefDeRang);
    // diningScene->addItem(chefDeRang->getGraphicsItem());

    // Employee *serveur1 = new Employee(3, "Steve", "Serveur", ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/serveur.png");
    // serveur1->setPosition(150, 50);
    // employeeController.addEmployee(serveur1);
    // diningScene->addItem(serveur1->getGraphicsItem());

    // Employee *serveur2 = new Employee(4, "Bob", "Serveur", ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/serveur.png");
    // serveur2->setPosition(200, 50);
    // employeeController.addEmployee(serveur2);
    // diningScene->addItem(serveur2->getGraphicsItem());

    // Employee *commis = new Employee(5, "Jacob", "Commis", ":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/commis.png");
    // commis->setPosition(250, 50);
    // employeeController.addEmployee(commis);
    // diningScene->addItem(commis->getGraphicsItem());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete diningScene;
    delete kitchenScene;

    if (logFile.isOpen()) {
        logMessage("Application terminée");
        logFile.close();
    }

    if (timer) {
        delete timer;
    }

    // Fermeture de la BD à l'arrêt
    if (db.isOpen()) {
        db.close();
    }

    delete socket;
    delete orderModel;
    delete menuController;

}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    // No need to override paintEvent for QGraphicsView
}


// Lancement de la simulation



// Ajouter les membres suivants à la classe MainWindow :
int maxGroupSize = 8;    // Par défaut
int simulationSpeed = 1; // Par défaut
QTime startTime;         // Défaut : 00:00

void MainWindow::openSettingsDialog() {
    GameSettings settingsDialog(this);

    if (settingsDialog.exec() == QDialog::Accepted) {
        // Récupérer les paramètres de l'utilisateur
        maxGroupSize = settingsDialog.getGroupSizeLimit();
        simulationSpeed = settingsDialog.getSimulationSpeed();
        startTime = settingsDialog.getStartTime();

        logMessage(QString("Paramètres mis à jour : Groupes max %1, Vitesse %2, Heure de démarrage %3")
                       .arg(maxGroupSize)
                       .arg(simulationSpeed)
                       .arg(startTime.toString("HH:mm")));
    }
}

void MainWindow::startSimulation() {
    if (!isRunning) {
        isRunning = true;

        timeScale = simulationSpeed;
        timer->start(1000 / timeScale);

        logMessage("Simulation démarrée");
        simulationTime = startTime.hour() * 3600 + startTime.minute() * 60;

        // Création de clients
        int clientId = QRandomGenerator::global()->bounded(1, 100);
        int groupSize = QRandomGenerator::global()->bounded(1, maxGroupSize);

        auto newClient = new Client(clientId, groupSize, this);
        clients.append(newClient);

        Table* table = tableController.findAvailableTable(groupSize);
        if (table) {
            table->setOccupied(true);
            newClient->setSeated(true);
            qDebug() << "Client" << clientId << "installé à la table" << table->getId();

            createOrder(clientId, table->getId());
        } else {
            qDebug() << "Aucune table disponible pour un groupe de taille" << groupSize;
        }

        // Mise à jour des informations
        // updateCustomerInfo();
        // updateTableInfo();
    }
}



void MainWindow::createOrder(int clientId, int tableId) {
    QList<Menu> menuItems = menuController->getAllMenus();
    if (menuItems.isEmpty()) {
        qDebug() << "Menu vide : impossible de passer une commande.";
        return;
    }

    int randomIndex = QRandomGenerator::global()->bounded(menuItems.size());
    QString dishName = menuItems[randomIndex].getName();
    int quantity = QRandomGenerator::global()->bounded(1, 8);

    QList<OrderItem> items = {{dishName, quantity}};
    orderModel->addOrder(clientId, tableId, items);

    qDebug() << "Commande créée pour le client" << clientId << ":"
             << dishName << "x" << quantity;
}

void MainWindow::markOrderReady(int tableId) {
    Table *table = tableController.findTableById(tableId);
    if (!table) {
        qDebug() << "Table non trouvée pour ID:" << tableId;
        return;
    }

    QGraphicsEllipseItem *indicator = new QGraphicsEllipseItem(0, 0, 10, 10, table);
    indicator->setBrush(Qt::red);
    indicator->setPos(10, 10);
    diningScene->addItem(indicator);

    qDebug() << "Commande prête pour la table" << tableId;
}



void MainWindow::onOrderAdded(int clientId, int tableId) {
    qDebug() << "Commande ajoutée:" << clientId << tableId;

    // Envoyer au serveur via socket
    QByteArray data = QString("ORDER_ADDED:%1:%2").arg(clientId).arg(tableId).toUtf8();
    socket->write(data);

    // Trouver le client et simuler son activité
    Client* client = clientController.findClientById(clientId);
    Table* table = tableController.findTableById(tableId);
    if (client && table) {
        simulateClientActivity(client, table);
    }
}


void MainWindow::onOrderRemoved(int clientId) {
    qDebug() << "Commande servie pour le client" << clientId;

    // Supprimer la commande de la QListWidget
    for (int i = 0; i < ui->orderList->count(); ++i) {
        QListWidgetItem *item = ui->orderList->item(i);
        if (item->text().startsWith(QString("Client %1").arg(clientId))) {
            delete ui->orderList->takeItem(i);
            break;
        }
    }

    // Envoyer au serveur via socket
    QByteArray data = QString("ORDER_REMOVED:%1").arg(clientId).toUtf8();
    socket->write(data);
}
void MainWindow::handleClientCommand(int clientId, int tableId, const QList<OrderItem> &items)
{
    qDebug() << "Commande reçue pour le client" << clientId << "à la table" << tableId;

    QString orderDescription = QString("Client %1 - Table %2:\n").arg(clientId).arg(tableId);
    for (const auto &item : items) {
        orderDescription += QString(" - %1 x%2\n").arg(item.first).arg(item.second);  // Utilisation de .first et .second pour QPair
    }

    // Ajouter la commande à la QListWidget
    if (ui->orderList) {
        ui->orderList->addItem(orderDescription);
    }

    // Récupérer la table en fonction de l'ID de la table
    Table *table = tableController.findTableById(tableId);
    if (!table) {
        qDebug() << "Table non trouvée pour l'ID:" << tableId;
        return;
    }

    // Représentation graphique de la commande
    QGraphicsEllipseItem *orderCircle = new QGraphicsEllipseItem(0, 0, 20, 20);
    orderCircle->setBrush(Qt::yellow);
    diningScene->addItem(orderCircle);

    // Positionner le cercle sur la même position que la table
    orderCircle->setPos(table->x(), table->y()); // Utilise la position de la table

    // Vous pouvez ajouter un décalage si vous souhaitez que le cercle soit légèrement au-dessus de la table
    orderCircle->setPos(table->x() + 4, table->y() - 4);

    // Délai pour la préparation de la commande (ex : 5 secondes)
    QTimer::singleShot(5000, [this, clientId, tableId, items, orderCircle, table]() {
        // Simuler la préparation de la commande (Livraison)
        qDebug() << "Commande livrée pour le client" << clientId << "à la table" << tableId;

        // Représentation de la livraison (changer la couleur du cercle)
        orderCircle->setBrush(Qt::green);

        // Délai pour que le client consomme la commande (ex : 3 secondes)
        QTimer::singleShot(3000, [this, clientId, tableId, orderCircle, table]() {
            // Simuler la consommation de la commande
            qDebug() << "Client" << clientId << "a terminé sa commande à la table" << tableId;

            // Supprimer le client de la scène
            diningScene->removeItem(table->getGraphicsItem());

            // Supprimer la commande de la scène après 2 seconde
            QTimer::singleShot(2000, [this, orderCircle]() {
                diningScene->removeItem(orderCircle);
                delete orderCircle;
            });
        });
    });
}

void MainWindow::serveOrder(int clientId) {
    qDebug() << "Commande servie pour le client" << clientId;

    // Ici, vous pourriez déclencher un signal ou une autre action pour servir la commande
    onOrderRemoved(clientId);  // Exemple pour marquer la commande comme servie
}



void MainWindow::handleSocketReadyRead() {
    while (socket->canReadLine()) {
        QByteArray data = socket->readLine().trimmed();
        qDebug() << "Message reçu du serveur :" << data;
    }
}




// Pause sur la simulation

void MainWindow::pauseSimulation()
{
    if (isRunning) {
        isRunning = false;
        timer->stop();

        for (auto timeline : clientTimelines) {
            if (timeline) {
                timeline->setPaused(true);
            }
        }

        logMessage("Simulation mise en pause");
    }
}


// Stop la simulation et update les scenes
void MainWindow::stopSimulation()
{
    if (isRunning) {
        pauseSimulation();
    }

    simulationTime = 0;
    ui->timeButton->setText("Heure : 00:00");

    // Nettoyage de la scène
    diningScene->clear();

    // Supprimer les timelines
    for (auto timeline : clientTimelines) {
        delete timeline;
    }
    clientTimelines.clear();

    // Supprimer les items clients
    for (auto client : clientItems) {
        delete client;
    }
    clientItems.clear();
    logMessage("Simulation arrêtée");
}


// Callback pour refresh le temps
void MainWindow::updateTime()
{
    simulationTime += timeScale;
    int hours = simulationTime / 3600;
    int minutes = (simulationTime % 3600) / 60;
    int seconds = simulationTime % 60;

    ui->timeButton->setText(QString("Heure : %1:%2:%3")
                                .arg(hours)
                                .arg(minutes, 2, 10, QChar('0'))
                                .arg(seconds, 2, 10, QChar('0')));

    logMessage(QString("Temps mis à jour : %1:%2:%3")
                   .arg(hours)
                   .arg(minutes, 2, 10, QChar('0'))
                   .arg(seconds, 2, 10, QChar('0')));
}

void MainWindow::accelSimulation()
{
    timeScale = (timeScale == 1) ? 2 : 1; // Basculer entre vitesse normale et accélérée
    timer->setInterval(1000 / timeScale); // Ajuster l'intervalle du timer

    for (auto timeline : clientTimelines) {
        if (timeline) {
            timeline->setDuration(timeline->duration() / timeScale);
        }
    }

    logMessage(timeScale == 2 ? "Mode simulation accéléré activé" : "Mode simulation normal activé");
}

void MainWindow::logMessage(const QString &message)
{
    if (logFile.isOpen()) {
        QTextStream out(&logFile);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " - " << message << "\n";
    }
    qDebug() << message;
}


// void MainWindow::keyPressEvent(QKeyEvent *event) {
//     if (isRunning && myRect) { // Ensure myRect is initialized
//         qreal step = 10.0;
//         QRectF sceneBounds = diningScene->sceneRect(); // Use diningScene

//         if (event->key() == Qt::Key_Left && myRect->x() - step >= sceneBounds.left()) {
//             myRect->setPos(myRect->x() - step, myRect->y());
//         } else if (event->key() == Qt::Key_Right && myRect->x() + step + myRect->boundingRect().width() <= sceneBounds.right()) {
//             myRect->setPos(myRect->x() + step, myRect->y());
//         } else if (event->key() == Qt::Key_Up && myRect->y() - step >= sceneBounds.top()) {
//             myRect->setPos(myRect->x(), myRect->y() - step);
//         } else if (event->key() == Qt::Key_Down && myRect->y() + step + myRect->boundingRect().height() <= sceneBounds.bottom()) {
//             myRect->setPos(myRect->x(), myRect->y() + step);
//         }

//         // Log x-coordinate to file
//         QFile file("movement_log.txt");
//         if (file.open(QIODevice::Append | QIODevice::Text)) {
//             QTextStream out(&file);
//             out << "x: " << myRect->x() << "\n";
//         }
//         file.close();

//         qDebug() << "MyRect moved to (" << myRect->x() << "," << myRect->y() << ")";
//     } else {
//         QMainWindow::keyPressEvent(event); // Default behavior
//     }
// }

// void MainWindow::openStockManagement()
// {
//     // Créer une instance de StockManagement
//     StockWindow *stockWindow = new StockWindow(this); // Passer `this` comme parent
//     stockWindow->show(); // Afficher la fenêtre
// }

// void MainWindow::openSettings()
// {
//     settingsDialog->show(); // Afficher la fenêtre Settings
// }

// void MainWindow::applySettings()
// {
//     QTime startTime = settingsDialog->getStartTime();
//     int groupSize = settingsDialog->getGroupSize();
//     int simulationSpeed = settingsDialog->getSimulationSpeed();

//     // Mettre à jour les paramètres de la simulation
//     timer->setInterval(1000 / simulationSpeed);
//     timeScale = simulationSpeed;
//     groupSize = groupSize;

//     // Autres mises à jour basées sur les paramètres
//     logMessage(QString("Paramètres appliqués : Heure de démarrage : %1, Taille max du groupe : %2, Vitesse de simulation : %3, Son : %4")
//                    .arg(startTime.toString())
//                    .arg(groupSize)
//                    .arg(simulationSpeed));
// }






void MainWindow::updateStockLevelsProgressBar() {
    QSqlQuery query;
    int totalQuantite = 0;
    int totalIngredients = 0;
    int quantiteMax = 100; // Quantité maximale pour un ingrédient

    // Requête SQL pour récupérer les quantités actuelles
    if (query.exec("SELECT quantite FROM ingredients")) {
        while (query.next()) {
            totalQuantite += query.value(0).toInt();
            totalIngredients++;
        }
    } else {
        qWarning() << "Erreur lors de la requête:" << query.lastError().text();
        return;
    }

    // Calcul du niveau de stock global
    int progressBarValue = 0;
    if (totalIngredients > 0) {
        progressBarValue = static_cast<int>(
            (static_cast<double>(totalQuantite) / (totalIngredients * quantiteMax)) * 100
            );
    }

    // Mettre à jour la ProgressBar
    ui->stockLevelsProgressBar->setValue(progressBarValue);

    // Gestion des messages et des couleurs
    QString message;
    QString color;

    if (progressBarValue < 20) {
        message = "Stock critique !";
        color = "red";
    } else if (progressBarValue < 50) {
        message = "Stock bas";
        color = "orange";
    } else if (progressBarValue < 80) {
        message = "Stock suffisant";
        color = "yellow";
    } else {
        message = "Stock optimal";
        color = "green";
    }

    // Appliquer la couleur à la ProgressBar via StyleSheet
    ui->stockLevelsProgressBar->setStyleSheet(
        QString("QProgressBar::chunk { background-color: %1; }").arg(color)
        );

    // Afficher le message dans un QLabel
    ui->stockLevelsLabel->setText(message);
}




// Occupation de chaque table
void MainWindow::updateTableSeatsProgressBar() {
    int totalCapacity = 0;
    int totalOccupied = 0;

    // Parcourez toutes les tables de votre contrôleur
    for (Table* table : tableController.getTables()) {
        totalCapacity += table->getCapacity();
        if (table->isOccupied()) {
            totalOccupied += table->getCapacity();
        }
    }

    // Calcul du pourcentage d'occupation
    int progressBarValue = 0;
    if (totalCapacity > 0) {
        progressBarValue = static_cast<int>((static_cast<double>(totalOccupied) / totalCapacity) * 100);
    }

    // Mettre à jour la ProgressBar
    ui->tableSeatsProgressBar->setValue(progressBarValue);

    // Gestion des messages et des couleurs
    QString message;
    QString color;

    if (progressBarValue == 100) {
        message = "Toutes les places sont occupées !";
        color = "red";
    } else if (progressBarValue > 80) {
        message = "Plus de place bientôt !";
        color = "orange";
    } else if (progressBarValue > 50) {
        message = "Place disponible";
        color = "yellow";
    } else {
        message = "Beaucoup de places disponibles";
        color = "green";
    }

    // Appliquer la couleur à la ProgressBar via StyleSheet
    ui->tableSeatsProgressBar->setStyleSheet(
        QString("QProgressBar::chunk { background-color: %1; }").arg(color)
        );

    // Afficher le message dans un QLabel
    ui->tableSeatsLabel->setText(message);
}



void MainWindow::updateCustomerInfo() {
    int totalClients = clients.size();
    int waitingClients = 0;
    int seatedClients = 0;

    for (const auto& client : clients) {
        if (!client->getIsSeated()) {
            waitingClients++;
        } else {
            seatedClients++;
        }
    }

    QString customerInfo = QString(
                               "<p><b>Infos clients:</b></p>"
                               "<p>- Total clients: %1</p>"
                               "<p>- Clients en attente: %2</p>"
                               "<p>- Clients assis: %3</p>")
                               .arg(totalClients)
                               .arg(waitingClients)
                               .arg(seatedClients);

    ui->customerInfoTextBrowser->setHtml(customerInfo);
}



// void MainWindow::updateTableInfo() {
//     int totalTables = tableController.getTables().size();
//     int occupiedTables = 0;

//     for (const auto& table : tableController.getTables()) {
//         if (table->isOccupied()) {
//             occupiedTables++;
//         }
//     }

//     int availableTables = totalTables - occupiedTables;

//     QString tableInfo = QString(
//                             "<p><b>Infos tables:</b></p>"
//                             "<p>- Total tables: %1</p>"
//                             "<p>- Tables occupées: %2</p>"
//                             "<p>- Tables disponibles: %3</p>")
//                             .arg(totalTables)
//                             .arg(occupiedTables)
//                             .arg(availableTables);

//     ui->tableInfoTextBrowser->setHtml(tableInfo);
// }





void MainWindow::simulateClientActivity(Client* client, Table* table) {
    // Logique pour simuler l'activité du client
    if (client->getIsSeated()) {
        // Si le client est assis, on peut simuler son activité
        qDebug() << "Simuler l'activité du client" << client->getId() << "à la table" << table->getId();

        // Exemple de simulation d'activité : passation de commande, consommation, etc.
        if (!client->getHasOrdered()) {
            client->setHasOrdered(true); // Marquer le client comme ayant commandé
            createOrder(client->getId(), table->getId()); // Créer une commande pour ce client
        }

        if (!client->getIsConsuming()) {
            client->setConsuming(true); // Marquer le client comme consommant
            qDebug() << "Client" << client->getId() << "est en train de manger à la table" << table->getId();
        }
    }
        // Mise à jour après départ
            // updateCustomerInfo();
            // updateTableInfo();

}
