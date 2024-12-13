#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lave.h"
#include "fridge.h"
#include "staff.h"
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
    setupStaff();


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
    connect(stockTimer, &QTimer::timeout, this, &MainWindow::loadStockInfo);
    connect(stockTimer, &QTimer::timeout, this, &MainWindow::updateStockLevelsProgressBar);
    connect(stockTimer, &QTimer::timeout, this, &MainWindow::updateTableSeatsProgressBar);
    connect(stockTimer, &QTimer::timeout, this, &MainWindow::loadInventoryData);
    connect(stockTimer, &QTimer::timeout, this, &MainWindow::loadMenuData);
    connect(stockTimer, &QTimer::timeout, this, &MainWindow::updateCustomerInfo);


    stockTimer->start(2000); // Rafraîchissement toutes les 2 secondes


    // Configuration des scènes
    ui->diningAreaView->setScene(diningScene);
    ui->kitchenAreaView->setScene(kitchenScene);



    // Connexion des boutons

    connect(ui->stratButton, &QPushButton::clicked, this, &MainWindow::startSimulation);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::pauseSimulation);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopSimulation);
    connect(ui->accelButton, &QPushButton::clicked, this, &MainWindow::accelSimulation);

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



// Les méthodes de la cuisine
void MainWindow::setupStaff() {
    // Configuration du chef
    QGraphicsPixmapItem *chefItem = new QGraphicsPixmapItem(QPixmap(":img/chef.png"));
    chefItem->setPos(300, -60); // Position du chef
    chefItem->setScale(0.1);  // Ajuste la taille si nécessaire
    kitchenScene->addItem(chefItem);

    // Configuration du serveur
    QGraphicsPixmapItem *serverItem = new QGraphicsPixmapItem(QPixmap(":img/serve.png"));
    serverItem->setPos(-100, -300); // Position du serveur
    serverItem->setScale(0.1);  // Ajuste la taille si nécessaire
    kitchenScene->addItem(serverItem);

    // Configuration du plongeur
    QGraphicsPixmapItem *plongeurItem = new QGraphicsPixmapItem(QPixmap(":img/plongeur.png"));
    plongeurItem->setPos(50, 150); // Position du plongeur
    plongeurItem->setScale(0.1);  // Ajuste la taille si nécessaire
    kitchenScene->addItem(plongeurItem);

    chefTargets = {
        QPointF(300, -150), // Position cible 1
        QPointF(50, -330),  // Position cible 2
        QPointF(350, 200)   // Position cible 3
    };
    currentTaskIndex = 0;

}


// Gestion de taches par Chef
void MainWindow::moveChefToNextTask() {
    if (chefTargets.isEmpty()) {
        qDebug() << "Aucune cible définie pour le chef.";
        return;
    }

    // Vérifier si on a atteint la dernière cible
    if (currentTaskIndex >= chefTargets.size()) {
        qDebug() << "Simulation terminée.";
        return; // Simulation terminée, ne pas bouger le chef
    }

    // Définir la prochaine position
    QPointF nextTarget = chefTargets[currentTaskIndex];
    currentTaskIndex++; // Passer à la prochaine cible

    // Configurer l'animation
    QPropertyAnimation *animation = new QPropertyAnimation(chefItem, "pos");
    animation->setDuration(2000); // Durée de l'animation (en millisecondes)
    animation->setStartValue(chefItem->pos());
    animation->setEndValue(nextTarget);
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    // Connecter la fin de l'animation pour lancer la suivante
    connect(animation, &QPropertyAnimation::finished, this, &MainWindow::moveChefToNextTask);

    animation->start();
    qDebug() << "Chef se déplace vers :" << nextTarget;
}





// Chargement des éléments du stock de l'ui

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



// Chargement du stock
void MainWindow::loadStockInfo() {
    QSqlQuery query("SELECT nom, quantite FROM ingredients");

    if (!query.exec()) {
        qDebug() << "Les informations du stock d'ingrédients ne sont pas chargées" << query.lastError().text();
        return;
    }

    QString html = R"(
         <p>Niveaux de stock: </p>
    )";

    while (query.next()) {
        QString ingredientName = query.value(0).toString();
        int quantity = query.value(1).toInt();

        html += QString(R"(
        <p>%1 (%2)</p>
    )").arg(ingredientName).arg(quantity);
    }
    ui->stockInfoTextBrowser->setHtml(html);
}


// Chargement de l'inventaire
void MainWindow::loadInventoryData() {
    QSqlQuery query("SELECT nom_item, quantite FROM inventaire");

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des données de l'inventaire:" << query.lastError().text();
        return;
    }

    QString html = R"(
            <p>Inventaire: </p>
    )";

    while (query.next()) {
        QString itemName = query.value(0).toString();
        int quantity = query.value(1).toInt();

        html += QString(R"(
            <p>%1 (%2)</p>
        )").arg(itemName).arg(quantity);
    }

    html += R"(
        </body>
        </html>
    )";

    // Afficher le HTML dans le widget tableInfoTextBrowser
    ui->tableInfoTextBrowser->setHtml(html);


    // Elements de la cuisine

    // table essaie0
    Lave *lave1 = new Lave(1, 1, ":img/frigo.png");
    lave1->setPosition(350, 200);
    lave1->setScale(1);
    laveController.addLave(lave1);
    kitchenScene->addItem(lave1->getGraphicsItem());

    Lave *lave2 = new Lave(2, 2, ":img/plaque.jpeg");
    lave2->setPosition(50, -330);
    laveController.addLave(lave2);
    kitchenScene->addItem(lave2->getGraphicsItem());

    Lave *lave3 = new Lave(3, 3, ":img/plaque.jpeg");
    lave3->setPosition(127, -330);
    laveController.addLave(lave1);
    kitchenScene->addItem(lave3->getGraphicsItem());

    Lave *lave4 = new Lave(4, 4, ":img/cuisine.png");
    lave4->setPosition(350, -150);
    lave4->setScale(0.1);
    laveController.addLave(lave4);
    kitchenScene->addItem(lave4->getGraphicsItem());


    Fridge *fridge1 = new Fridge(1, 4, ":img/compt.png");
    fridge1->setPosition(-170, -330);
    fridge1->setScale(00.1);  // Ajuste la taille si nécessaire
    fridgeController.addFridge(fridge1);
    kitchenScene->addItem(fridge1->getGraphicsItem());


    Fridge *fridge2 = new Fridge(2, 4, ":img/lave-vaisselle.png");
    fridge2->setPosition(-170,170);
    fridgeController.addFridge(fridge2);
    kitchenScene->addItem(fridge2->getGraphicsItem());


   // Ajouter des tables

    Table *table10 = new Table(10, 8, ":img/table_3.png");
    table10->setPosition(-200, -210);
    tableController.addTable(table10);
    diningScene->addItem(table10->getGraphicsItem());

    Table *table11 = new Table(11, 8, ":img/table_3.png");
    table11->setPosition(-200, -210);
    tableController.addTable(table11);
    diningScene->addItem(table11->getGraphicsItem());

    Table *table12 = new Table(4, 1, ":img/table_3.png");
    table12->setPosition(-200, -210);
    tableController.addTable(table12);
    diningScene->addItem(table12->getGraphicsItem());

    Table *table2 = new Table(4, 1, ":img/table_3.png");
    table2->setPosition(120, -110);
    tableController.addTable(table2);
    diningScene->addItem(table2->getGraphicsItem());

    Table *table3 = new Table(3, 8, ":img/table_3.png");
    table3->setPosition(40, -110);
    tableController.addTable(table3);
    diningScene->addItem(table3->getGraphicsItem());

    Table *table6 = new Table(6, 8, ":img/table_3.png");
    table6->setPosition(-90, -110);
    tableController.addTable(table6);
    diningScene->addItem(table6->getGraphicsItem());

    Table *table5 = new Table(5, 4, ":img/table_3.png");
    table5->setPosition(-120, 160);
    tableController.addTable(table5);
    diningScene->addItem(table5->getGraphicsItem());

    Table *table7 = new Table(7, 8, ":img/table_3.png");
    table7->setPosition(-40, 160);
    tableController.addTable(table7);
    diningScene->addItem(table7->getGraphicsItem());

    // Table *table8 = new Table(8, 4, ":img/table_3.png");
    // table8->setPosition(40, 160);
    // tableController.addTable(table8);
    // diningScene->addItem(table8->getGraphicsItem());

    // Table *table9 = new Table(4, 4, ":img/table_3.png");
    // table9->setPosition(120, 160);
    // tableController.addTable(table9);
    // diningScene->addItem(table9->getGraphicsItem());


    // Table *table14 = new Table(14, 8, ":img/table_3.png");
    // table14->setPosition(40, 60);
    // tableController.addTable(table14);
    // diningScene->addItem(table14->getGraphicsItem());

    // Table *table16 = new Table(16, 8, ":img/table_3.png");
    // table16->setPosition(-40, 60);
    // tableController.addTable(table16);
    // diningScene->addItem(table16->getGraphicsItem());

    // Table *table15 = new Table(15, 4, ":img/table_3.png");
    // table15->setPosition(-90, 60);
    // tableController.addTable(table15);
    // diningScene->addItem(table15->getGraphicsItem());



    // Employee *chefDeRang = new Employee(2, "Daniel", "Chef de Rang", ":img/rang.png");
    // chefDeRang->setPosition(100, 50);
    // employeeController.addEmployee(chefDeRang);
    // diningScene->addItem(chefDeRang->getGraphicsItem());

    // Employee *serveur1 = new Employee(3, "Steve", "Serveur", ":img/serveur.png");
    // serveur1->setPosition(150, 50);
    // employeeController.addEmployee(serveur1);
    // diningScene->addItem(serveur1->getGraphicsItem());

    // Employee *serveur2 = new Employee(4, "Bob", "Serveur", ":img/serveur.png");
    // serveur2->setPosition(200, 50);
    // employeeController.addEmployee(serveur2);
    // diningScene->addItem(serveur2->getGraphicsItem());

    // Employee *commis = new Employee(5, "Jacob", "Commis", ":img/commis.png");
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
    delete threadPool;

}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    // No need to override paintEvent for QGraphicsView
}


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



// Commencer la simulation
void MainWindow::startSimulation() {
    if (!isRunning) {
        isRunning = true;

        // timeScale = simulationSpeed;
        timer->start(1000);

        qDebug() << "Simulation démarrée";
        // simulationTime = startTime.hour() * 3600 + startTime.minute() * 60;


        // Cuisine Motion et gestion des états
        Lave *chef = new Lave(5, 4, ":img/chef.png");
        chef->setPosition(350, -150);
        chef->setScale(0.1);
        laveController.addLave(chef);
        kitchenScene->addItem(chef->getGraphicsItem());



        // ---- Animation du déplacement du Chef ----
        QTimeLine *chefTimeline = new QTimeLine(5000, this); // Durée 5 secondes
        chefTimeline->setFrameRange(0, 100);
        chefTimeline->setLoopCount(0); // Déplacement en boucle


        connect(chefTimeline, &QTimeLine::frameChanged, this, [=](int frame) {
            // Interpolation linéaire entre les coordonnées initiales (300, -100) et finales (127, -300)
            qreal progress = frame / 100.0;
            qreal x = 300 + progress * (127 - 300);
            qreal y = -100 + progress * (-300 + 100);
            chef->getGraphicsItem()->setPos(x, y);
        });

        connect(chefTimeline, &QTimeLine::finished, this, [=]() {
            qDebug() << "Chef est arrivé à destination (127, -300).";
        });

        chefTimeline->start();
        clientTimelines.append(chefTimeline);

        Lave *personnage1 = new Lave(6, 4, ":img/commis.png");
        personnage1->setPosition(350, -150);
        personnage1->setScale(0.1);


        laveController.addLave(personnage1);
        kitchenScene->addItem(personnage1->getGraphicsItem());

        QTimeLine *personnage1Timeline = new QTimeLine(5000, this); // Durée 5 secondes
        personnage1Timeline->setFrameRange(0, 100);
        personnage1Timeline->setLoopCount(0); // Déplacement en boucle

        connect(personnage1Timeline, &QTimeLine::frameChanged, this, [=](int frame) {
            // Interpolation linéaire entre les coordonnées initiales (60, 150) et finales (-100, -290)
            qreal progress = frame / 100.0;
            qreal x = 60 + progress * (-100 - 60);
            qreal y = 150 + progress * (-290 - 150);
            personnage1->getGraphicsItem()->setPos(x, y);
        });

        personnage1Timeline->start();
        clientTimelines.append(personnage1Timeline);

        Lave *personnage2 = new Lave(7, 4, ":img/commis.png");
        personnage2->setPosition(350, -150);
        personnage2->setScale(0.1);
        laveController.addLave(personnage2);
        kitchenScene->addItem(personnage2->getGraphicsItem());

        QTimeLine *personnage2Timeline = new QTimeLine(5000, this); // Durée 5 secondes
        personnage2Timeline->setFrameRange(0, 100);
        personnage2Timeline->setLoopCount(0); // Déplacement en boucle

        connect(personnage2Timeline, &QTimeLine::frameChanged, this, [=](int frame) {
            // Interpolation linéaire entre les coordonnées initiales (-100, -310) et finales (70, 150)
            qreal progress = frame / 100.0;
            qreal x = -100 + progress * (70 + 100);
            qreal y = -310 + progress * (150 + 310);
            personnage2->getGraphicsItem()->setPos(x, y);
        });

        personnage2Timeline->start();
        clientTimelines.append(personnage2Timeline);


        // Sallon motion et gestion des états


        // Création de clients

                // Configurer un QTimer pour créer des clients toutes les 2 secondes
                QTimer* clientCreationTimer = new QTimer(this);
                connect(clientCreationTimer, &QTimer::timeout, this, [=, this]() {
                    // Création d'un seul client à chaque tick
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

                    // Optionnel : Limiter la taille de la liste des clients pour éviter la surcharge
                    if (clients.size() > 100) { // Supposons une limite de 100 clients
                        delete clients.takeFirst(); // Supprime les plus anciens
                    }
                });

                clientCreationTimer->start(3000); // Intervalle de 3 secondes
            }
        }



void MainWindow::createOrder(int clientId, int tableId) {
    QList<Menu> menuItems = menuController->getAllMenus();
    if (menuItems.isEmpty()) {
        qDebug() << "Menu vide : impossible de passer une commande.";
        return;
    }

    int totalQuantity = QRandomGenerator::global()->bounded(1, 8);
    QList<OrderItem> items;

    for (int i = 0; i < totalQuantity; ++i) {
        int randomIndex = QRandomGenerator::global()->bounded(menuItems.size());
        QString dishName = menuItems[randomIndex].getName();
        int quantity = 1; // Chaque menu est commandé une fois
        items.append({dishName, quantity});
    }

    orderModel->addOrder(clientId, tableId, items);

    // Mettre à jour la quantité des ingrédients pour chaque menu commandé
    for (const auto &item : items) {
        menuController->updateIngredientQuantities(item.first, item.second);
    }

    qDebug() << "Commande créée pour le client" << clientId << ":"
             << items;
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

void MainWindow::handleClientCommand(int clientId, int tableId, const QList<OrderItem> &items) {
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

    // Charger l'image PNG
    QPixmap orderPixmap(":/images/order.png"); // Assurez-vous que le chemin est correct
    QGraphicsPixmapItem *orderItem = new QGraphicsPixmapItem(orderPixmap);

    // Positionner l'image sur la même position que la table
    orderItem->setPos(table->x(), table->y()); // Utilise la position de la table

    // Ajouter l'image à la scène
    diningScene->addItem(orderItem);

    // Délai pour la préparation de la commande (ex : 5 secondes)
    QTimer::singleShot(5000, [this, clientId, tableId, items, orderItem, table]() {
        // Simuler la préparation de la commande (Livraison)
        qDebug() << "Commande livrée pour le client" << clientId << "à la table" << tableId;

        // Représentation de la livraison (changer l'image pour une autre image PNG)
        QPixmap deliveredPixmap(":/img/alimentation-saine.ico"); // Assurez-vous que le chemin est correct
        orderItem->setPixmap(deliveredPixmap);

        // Délai pour que le client consomme la commande (ex : 3 secondes)
        QTimer::singleShot(3000, [this, clientId, tableId, orderItem, table]() {
            // Simuler la consommation de la commande
            qDebug() << "Client" << clientId << "a terminé sa commande à la table" << tableId;

            // Supprimer le client de la scène
            diningScene->removeItem(table->getGraphicsItem());

            // Supprimer la commande de la scène après 2 secondes
            QTimer::singleShot(2000, [this, orderItem]() {
                diningScene->removeItem(orderItem);
                delete orderItem;
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
}

void MainWindow::showAlerts() {
    QDialog dialog(this);
    alertes->showAlerts(&dialog, clients, tableController.getTables(), employeeController.getEmployees());
}



// Le mode pause de la simulation
void MainWindow::pauseSimulation() {
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


// Accelerer la simulation

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


// Stopper la simulation
void MainWindow::stopSimulation() {
    if (isRunning) {
        pauseSimulation();
    }

    simulationTime = 0;
    ui->timeButton->setText("Heure : 00:00");

    // Nettoyage de la scène
    diningScene->clear();
    kitchenScene->clear();


    // Suppression des timelines
    for (auto timeline : clientTimelines) {
        delete timeline;
    }
    clientTimelines.clear();

    // Suppression des items clients
    for (auto client : clientItems) {
        delete client;
    }
    clientItems.clear();

    logMessage("Simulation arrêtée");
}


// Mettre à jour le timer
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
// Journalisation les events du programme
void MainWindow::logMessage(const QString &message)
{
    if (logFile.isOpen()) {
        QTextStream out(&logFile);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " - " << message << "\n";
    }
    qDebug() << message;
}


// Mettre à jour la barre de progression du stock en fonction de la quantité maximale pour un ingrédient.
void MainWindow::updateStockLevelsProgressBar() {
    QSqlQuery query;
    int totalQuantite = 0;
    int totalIngredients = 0;
    int quantiteMax = 1000;

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




// Mettre à jour les détails du resto
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

    // Calcul du taux de satisfaction (simple exemple)
    int satisfactionRate = totalClients == 0 ? 0 : (seatedClients * 100) / totalClients;

    QString customerInfo = QString(
                               "<p><b>Infos clients:</b></p>"
                               "<p>- Total clients: %1</p>"
                               "<p>- Clients en attente: %2</p>"
                               "<p>- Clients assis: %3</p>")
                               .arg(totalClients)
                               .arg(waitingClients)
                               .arg(seatedClients);

    ui->customerInfoTextBrowser->setHtml(customerInfo);

    QString message;
    QString color;


    if (satisfactionRate == 100) {
        message = "🙂";  // Très insatisfait
        color = "green";
    } else if (satisfactionRate > 80) {
        message = "😶";  // Insatisfait
        color = "orange";
    } else if (satisfactionRate > 50) {
        message = "😑";  // Moyennement satisfait
        color = "yellow";
    } else {
        message = "😡";  // Satisfait
        color = "red";
    }

    // Mettre à jour la ProgressBar
    ui->clientMoodProgressBar->setValue(satisfactionRate);  // Met le pourcentage dans la ProgressBar


    // Appliquer le style couleur
    ui->clientMoodProgressBar->setStyleSheet(
        QString("QProgressBar::chunk { background-color: %1; }").arg(color)
        );

    // Ajouter un emoji dans un QLabel, si souhaité
    ui->clientMoodLabel->setText(message);  // Supposez que vous avez un QLabel nommé emojiLabel
}



// Ouvrir le panneau de configuration de la simulation
void MainWindow::on_paramButton_clicked()
{
    GameSettings *dialog = new GameSettings();
    dialog->setWindowModality(Qt::WindowModality::NonModal);
    dialog->setMinimumWidth(410);
    dialog->setMinimumHeight(310);
    dialog->show();

}



// Ouvrir le menu de gestion du stock des ingrédients
void MainWindow::on_livraisonButton_clicked()
{
    stockWindow *stockWindow = new class stockWindow();
    stockWindow->setWindowModality(Qt::WindowModality::NonModal);
    // dialog->setMinimumWidth(410);
    // dialog->setMinimumHeight(310);
    stockWindow->show();
}



// Ouvrir le menu de controle d'affichage des alertes
void MainWindow::on_alertButton_clicked()
{
    ControlDialog *control = new ControlDialog();
    control->setWindowModality(Qt::WindowModality::NonModal);
    // dialog->setMinimumWidth(410);
    // dialog->setMinimumHeight(310);
    control->show();
}




