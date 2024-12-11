#include "mainwindow.h"
#include "lave.h"
#include "fridge.h"
#include "staff.h"
#include "ui_mainwindow.h"
#include "ingredients.h"
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>
#include <QTimeLine>
#include <cstdlib>
#include <QDir>
#include <QTextStream>
#include <QDateTime>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    isRunning(false),
    simulationTime(0),
    timeScale(1),
    diningScene(new QGraphicsScene(this)),
    kitchenScene(new QGraphicsScene(this)),
    timer(new QTimer(this)),
    logFile(QCoreApplication::applicationDirPath() + "/log/simulation.log")
{
    ui->setupUi(this);

    if (connectToDatabase()) {
        loadMenuData();
         loadStockInfo();
        loadInventoryData();
         logMessage("Base de données connectée");
    }
//moneraa
    setupStaff();





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

    Table *table4 = new Table(4, 1, ":/img/lav.png");
    table4->setPosition(50, 200);
    table4->setScale(0.2);  // Ajuste la taille si nécessaire
    tableController.addTable(table4);
    kitchenScene->addItem(table4->getGraphicsItem());



    // Configuration des scènes
    ui->diningAreaView->setScene(diningScene);
    ui->kitchenAreaView->setScene(kitchenScene);

    // Connexion des boutons
    connect(ui->stratButton, &QPushButton::clicked, this, &MainWindow::startSimulation);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::pauseSimulation);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopSimulation);
    connect(ui->accelButton, &QPushButton::clicked, this, &MainWindow::accelSimulation);
    // Connecter le signal dataChanged du modèle au slot updateUI de la fenêtre
    // connect(ingredients, &Ingredients::dataChanged, this, &MainWindow::updateUI);

    // Exemple de bouton pour ajouter des ingrédients
    // connect(ui->livraisonButton, &QPushButton::clicked, ingredients, &Ingredients::addIngredients);

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
   // qDebug() << "BD connectée.";
    return true;
}

//monera

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

// void MainWindow::moveChefToNextTask() {
//     if (chefTargets.isEmpty()) {
//         qDebug() << "Aucune cible définie pour le chef.";
//         return;
//     }

//     // Définir la prochaine position
//     QPointF nextTarget = chefTargets[currentTaskIndex];
//     currentTaskIndex = (currentTaskIndex + 1) % chefTargets.size(); // Passer à la prochaine cible

//     // Configurer l'animation
//     QPropertyAnimation *animation = new QPropertyAnimation(chef, "pos");
//     animation->setDuration(2000); // Durée en millisecondes
//     animation->setEndValue(nextTarget);
//     animation->setEasingCurve(QEasingCurve::InOutQuad);



//     animation->start();
//     qDebug() << "Chef se déplace vers :" << nextTarget;
// }

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
        <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">
        <html>
        <head>
            <meta name="qrichtext" content="1" />
            <meta charset="utf-8" />
            <style type="text/css">
                p, li { white-space: pre-wrap; }
                hr { height: 1px; border-width: 0; }
            </style>
        </head>
        <body style=" font-family:'Segoe UI'; font-size:12px; font-weight:400; font-style:normal;">
            <p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">
                <span style=" font-family:'MS Shell Dlg 2'; font-size:8.25pt;">Inventaire:</span>
            </p>
    )";

    // Parcourir les résultats et les ajouter au HTML
    while (query.next()) {
        QString itemName = query.value(0).toString();
        int quantity = query.value(1).toInt();

        html += QString(R"(
            <p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">
                <span style=" font-family:'MS Shell Dlg 2'; font-size:8.25pt;">%1 (%2)</span>
            </p>
        )").arg(itemName).arg(quantity);
    }

    html += R"(
        </body>
        </html>
    )";

    // Afficher le HTML dans le widget tableInfoTextBrowser
    ui->tableInfoTextBrowser->setHtml(html);
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

    // Fermeture de la BD à l'arret
    if (db.isOpen()) {
        db.close();
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    // No need to override paintEvent for QGraphicsView
}



void MainWindow::startSimulation()
{
    // moveChefToNextTask();
    // Démarrer le déplacement du chef

    if (!isRunning) {
        isRunning = true;
        timer->start(1000); // 1 seconde de temps réel = 1 seconde de simulation
        qDebug() << "Simulation démarrée";

        Lave *chef = new Lave(5, 4, ":img/chef.png");
        chef->setPosition(350, -150);
        chef->setScale(0.1);
        laveController.addLave(chef);
        kitchenScene->addItem(chef->getGraphicsItem());



        // ---- Création du Chef ----
        // Plongeur *chef = new Plongeur(":/img/chef.png", 1001); // Identifiant unique : 1001
        // chef->setPosition(300, -100, 60.0); // Position initiale du chef
        // chef->setScale(00.1);
        // kitchenScene->addItem(chef->getGraphicsItem());

        // QGraphicsPixmapItem *chefItem = new QGraphicsPixmapItem(QPixmap(":img/chef.png"));
        // chefItem->setPos(300, -100); // Position du chef
        // chefItem->setScale(0.1);  // Ajuste la taille si nécessaire
        // kitchenScene->addItem(chefItem);



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

        // Création de groupes de clients
        for (int i = 0; i < 5; ++i) { // 5 groupes par exemple
            int groupSize = rand() % 8 + 1; // Taille entre 1 et 8
            QList<QGraphicsPixmapItem *> group;  // Liste pour les clients du groupe

            for (int j = 0; j < groupSize; ++j) {
                // Créez un client avec un chemin d'image et un identifiant unique
                Client *client = new Client(":build/Desktop_Qt_MinGW_64_bit_31ccaa-Release/release/img/client_2.png", i * 2 + j);
                client->setPosition(0, i * 20 + j * 10, 60.0); // Position initiale
                diningScene->addItem(client->getGraphicsItem());
                clientController.addClient(client);
                group.append(client->getGraphicsItem()); // Ajoutez le client au groupe
            }

            // Animation pour le groupe
            int duration = rand() % 3000 + 8000; //
            QTimeLine *timeline = new QTimeLine(duration, this);
            timeline->setFrameRange(0, 100);

            connect(timeline, &QTimeLine::frameChanged, this, [=](int frame) {
                for (int k = 0; k < group.size(); ++k) {
                    int randomOffsetX = rand() % 20 - 8; // Décalage aléatoire X
                    int randomOffsetY = rand() % 5 - 15; // Décalage aléatoire Y

                    int x = frame * 5 + randomOffsetX; // Mouvement horizontal
                    int y = 50 + i * 60 + k * 10 + randomOffsetY; // Position verticale
                    group[k]->setPos(x, y); // Déplace le client dans le groupe
                }
            });

            connect(timeline, &QTimeLine::finished, this, [=, this]() {
                for (auto clientItem : group) {
                    Client *client = clientController.findClientById(clientItem->data(0).toInt());
                    if (client) {
                        client->showOrderPopup("Commandez vos plats", diningScene);
                    }
                }
                qDebug() << QString("Groupe %1 invité à passer commande").arg(i + 1);
            });

            timeline->start();
            clientTimelines.append(timeline);
        }
    }
}

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

void MainWindow::showPopup(const QString &message, QGraphicsItem *client)
{
    auto popup = new QGraphicsTextItem(message);
    popup->setDefaultTextColor(Qt::blue);
    popup->setFont(QFont("Arial", 12));
    popup->setZValue(1); // Affichage au-dessus
    popup->setPos(client->x(), client->y() - 30); // Position au-dessus du client

    diningScene->addItem(popup);

    QTimer::singleShot(2000, [=, this]() {
        diningScene->removeItem(popup);
        delete popup;
    });
}

void MainWindow::logMessage(const QString &message)
{
    if (logFile.isOpen()) {
        QTextStream out(&logFile);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " - " << message << "\n";
    }
    qDebug() << message;

}





void MainWindow::updateIngredients() {
    // Example of modifying the database and triggering UI update
    QSqlQuery query;
    query.exec("UPDATE ingredients SET quantite = quantite + 100");

    // Optionally, you can force a manual update after a change
    // updateDatabase();
}




// void updateUI() {
//     // Exemple de mise à jour de l'UI avec la nouvelle liste des ingrédients
//     QSqlQuery query("SELECT nom, quantite FROM ingredients");

//     if (query.exec()) {
//         ui->stockInfoTextBrowser->clear();
//         while (query.next()) {
//             QString name = query.value(0).toString();
//             int quantity = query.value(1).toInt();
//             ui->stockInfoTextBrowser->append(QString("%1 (%2)").arg(name).arg(quantity));
//         }
//     } else {
//         qDebug() << "Erreur mise à jour : " << query.lastError().text();
//     }

// }


