/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *headerFrame;
    QHBoxLayout *horizontalLayout;
    QPushButton *stratButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QPushButton *accelButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *timeButton;
    QPushButton *alertButton;
    QPushButton *livraisonButton;
    QPushButton *paramButton;
    QFrame *mainFrame;
    QHBoxLayout *horizontalLayout_2;
    QFrame *leftActionButtonsFrame;
    QVBoxLayout *verticalLayout_4;
    QTextBrowser *stockInfoTextBrowser;
    QPushButton *pushButton;
    QListWidget *orderList;
    QFrame *diningAreaFrame;
    QVBoxLayout *verticalLayout_2;
    QLabel *diningAreaLabel;
    QGraphicsView *diningAreaView;
    QFrame *kitchenAreaFrame;
    QVBoxLayout *verticalLayout_3;
    QLabel *kitchenAreaLabel;
    QGraphicsView *kitchenAreaView;
    QFrame *rightInfoFrame;
    QVBoxLayout *verticalLayout_5;
    QPushButton *customerMoodButton;
    QListWidget *menuListWidget;
    QTextBrowser *tableInfoTextBrowser;
    QTextBrowser *customerInfoTextBrowser;
    QFrame *dashboardFrame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *stockLevelsLabel;
    QProgressBar *stockLevelsProgressBar;
    QLabel *tableSeatsLabel;
    QProgressBar *tableSeatsProgressBar;
    QLabel *clientMoodLabel;
    QProgressBar *clientMoodProgressBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1746, 820);
        MainWindow->setStyleSheet(QString::fromUtf8("/* Background principal */\n"
"QWidget {\n"
"    background-color: #1e1e2e;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"/* Boutons */\n"
"QPushButton {\n"
"    selection-color: red;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    color: white;\n"
"    font: bold 14px \"Segoe UI\";\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #7366ff;  \n"
"    border-color: #8080ff;\n"
" \n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #282850; \n"
"}\n"
"\n"
"/* Labels */\n"
"QLabel {\n"
"    font: bold 16px \"Segoe UI\";\n"
"    color: #ffffff;\n"
"    background-color: transparent;\n"
"    text-align: center;\n"
"}\n"
"\n"
"/* Frames */\n"
"QFrame {\n"
"    background-color: #2e2e3e;\n"
"    border: 2px solid #5e5edc;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"/* Progress Bars */\n"
"QProgressBar {\n"
"    border: 2px solid #3a3a5f;\n"
"    border-radius: 5px;\n"
"    background: #2e2e3e;\n"
"    text-align: center;\n"
"    color: white;\n"
"    font: bold 12px \"Segoe UI\";\n"
"}\n"
""
                        "\n"
"QProgressBar::chunk {\n"
"    width: 20px;\n"
"}\n"
"\n"
"/* Text Browsers */\n"
"QTextBrowser {\n"
"    border: 2px solid #3a3a5f;\n"
"    border-radius: 10px;\n"
"    background-color: #2e2e3e;\n"
"    color: white;\n"
"    font: 12px \"Segoe UI\";\n"
"    padding: 10px;\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        headerFrame = new QFrame(centralwidget);
        headerFrame->setObjectName("headerFrame");
        headerFrame->setFrameShape(QFrame::Shape::StyledPanel);
        headerFrame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(headerFrame);
        horizontalLayout->setObjectName("horizontalLayout");
        stratButton = new QPushButton(headerFrame);
        stratButton->setObjectName("stratButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/jouer.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        stratButton->setIcon(icon);
        stratButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(stratButton);

        pauseButton = new QPushButton(headerFrame);
        pauseButton->setObjectName("pauseButton");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/pause.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pauseButton->setIcon(icon1);
        pauseButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(pauseButton);

        stopButton = new QPushButton(headerFrame);
        stopButton->setObjectName("stopButton");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/bouton-darret.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        stopButton->setIcon(icon2);
        stopButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(stopButton);

        accelButton = new QPushButton(headerFrame);
        accelButton->setObjectName("accelButton");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/avance-rapide.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        accelButton->setIcon(icon3);
        accelButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(accelButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        timeButton = new QPushButton(headerFrame);
        timeButton->setObjectName("timeButton");

        horizontalLayout->addWidget(timeButton);

        alertButton = new QPushButton(headerFrame);
        alertButton->setObjectName("alertButton");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/cercle.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alertButton->setIcon(icon4);
        alertButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(alertButton);

        livraisonButton = new QPushButton(headerFrame);
        livraisonButton->setObjectName("livraisonButton");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/img/inventaire (1).png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        livraisonButton->setIcon(icon5);
        livraisonButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(livraisonButton);

        paramButton = new QPushButton(headerFrame);
        paramButton->setObjectName("paramButton");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/img/parametres.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        paramButton->setIcon(icon6);
        paramButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(paramButton);


        verticalLayout->addWidget(headerFrame);

        mainFrame = new QFrame(centralwidget);
        mainFrame->setObjectName("mainFrame");
        mainFrame->setFrameShape(QFrame::Shape::StyledPanel);
        mainFrame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(mainFrame);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        leftActionButtonsFrame = new QFrame(mainFrame);
        leftActionButtonsFrame->setObjectName("leftActionButtonsFrame");
        leftActionButtonsFrame->setFrameShape(QFrame::Shape::StyledPanel);
        leftActionButtonsFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(leftActionButtonsFrame);
        verticalLayout_4->setObjectName("verticalLayout_4");
        stockInfoTextBrowser = new QTextBrowser(leftActionButtonsFrame);
        stockInfoTextBrowser->setObjectName("stockInfoTextBrowser");
        stockInfoTextBrowser->setMinimumSize(QSize(200, 90));
        stockInfoTextBrowser->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_4->addWidget(stockInfoTextBrowser);

        pushButton = new QPushButton(leftActionButtonsFrame);
        pushButton->setObjectName("pushButton");

        verticalLayout_4->addWidget(pushButton);

        orderList = new QListWidget(leftActionButtonsFrame);
        new QListWidgetItem(orderList);
        new QListWidgetItem(orderList);
        new QListWidgetItem(orderList);
        new QListWidgetItem(orderList);
        new QListWidgetItem(orderList);
        orderList->setObjectName("orderList");

        verticalLayout_4->addWidget(orderList);


        horizontalLayout_2->addWidget(leftActionButtonsFrame);

        diningAreaFrame = new QFrame(mainFrame);
        diningAreaFrame->setObjectName("diningAreaFrame");
        diningAreaFrame->setFrameShape(QFrame::Shape::StyledPanel);
        diningAreaFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(diningAreaFrame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        diningAreaLabel = new QLabel(diningAreaFrame);
        diningAreaLabel->setObjectName("diningAreaLabel");
        diningAreaLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(diningAreaLabel);

        diningAreaView = new QGraphicsView(diningAreaFrame);
        diningAreaView->setObjectName("diningAreaView");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(diningAreaView->sizePolicy().hasHeightForWidth());
        diningAreaView->setSizePolicy(sizePolicy);
        diningAreaView->setMinimumSize(QSize(600, 600));
        diningAreaView->setMaximumSize(QSize(600, 600));
        diningAreaView->setStyleSheet(QString::fromUtf8("QGraphicsView {\n"
"    background-image: url(:img/sol.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        diningAreaView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        diningAreaView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::NoBrush);
        diningAreaView->setBackgroundBrush(brush);

        verticalLayout_2->addWidget(diningAreaView);

        diningAreaView->raise();
        diningAreaLabel->raise();

        horizontalLayout_2->addWidget(diningAreaFrame);

        kitchenAreaFrame = new QFrame(mainFrame);
        kitchenAreaFrame->setObjectName("kitchenAreaFrame");
        kitchenAreaFrame->setFrameShape(QFrame::Shape::StyledPanel);
        kitchenAreaFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(kitchenAreaFrame);
        verticalLayout_3->setObjectName("verticalLayout_3");
        kitchenAreaLabel = new QLabel(kitchenAreaFrame);
        kitchenAreaLabel->setObjectName("kitchenAreaLabel");
        kitchenAreaLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(kitchenAreaLabel);

        kitchenAreaView = new QGraphicsView(kitchenAreaFrame);
        kitchenAreaView->setObjectName("kitchenAreaView");
        kitchenAreaView->setMinimumSize(QSize(600, 600));
        kitchenAreaView->setStyleSheet(QString::fromUtf8("QGraphicsView {\n"
"    background-image: url(:img/sol.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        kitchenAreaView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        kitchenAreaView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

        verticalLayout_3->addWidget(kitchenAreaView);

        kitchenAreaView->raise();
        kitchenAreaLabel->raise();

        horizontalLayout_2->addWidget(kitchenAreaFrame);

        rightInfoFrame = new QFrame(mainFrame);
        rightInfoFrame->setObjectName("rightInfoFrame");
        rightInfoFrame->setFrameShape(QFrame::Shape::StyledPanel);
        rightInfoFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(rightInfoFrame);
        verticalLayout_5->setObjectName("verticalLayout_5");
        customerMoodButton = new QPushButton(rightInfoFrame);
        customerMoodButton->setObjectName("customerMoodButton");

        verticalLayout_5->addWidget(customerMoodButton);

        menuListWidget = new QListWidget(rightInfoFrame);
        new QListWidgetItem(menuListWidget);
        new QListWidgetItem(menuListWidget);
        new QListWidgetItem(menuListWidget);
        menuListWidget->setObjectName("menuListWidget");
        menuListWidget->setMinimumSize(QSize(200, 200));

        verticalLayout_5->addWidget(menuListWidget);

        tableInfoTextBrowser = new QTextBrowser(rightInfoFrame);
        tableInfoTextBrowser->setObjectName("tableInfoTextBrowser");
        tableInfoTextBrowser->setMinimumSize(QSize(200, 100));

        verticalLayout_5->addWidget(tableInfoTextBrowser);

        customerInfoTextBrowser = new QTextBrowser(rightInfoFrame);
        customerInfoTextBrowser->setObjectName("customerInfoTextBrowser");
        customerInfoTextBrowser->setMinimumSize(QSize(200, 100));

        verticalLayout_5->addWidget(customerInfoTextBrowser);


        horizontalLayout_2->addWidget(rightInfoFrame);


        verticalLayout->addWidget(mainFrame);

        dashboardFrame = new QFrame(centralwidget);
        dashboardFrame->setObjectName("dashboardFrame");
        dashboardFrame->setFrameShape(QFrame::Shape::StyledPanel);
        dashboardFrame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_3 = new QHBoxLayout(dashboardFrame);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        stockLevelsLabel = new QLabel(dashboardFrame);
        stockLevelsLabel->setObjectName("stockLevelsLabel");

        horizontalLayout_3->addWidget(stockLevelsLabel);

        stockLevelsProgressBar = new QProgressBar(dashboardFrame);
        stockLevelsProgressBar->setObjectName("stockLevelsProgressBar");
        stockLevelsProgressBar->setValue(70);

        horizontalLayout_3->addWidget(stockLevelsProgressBar);

        tableSeatsLabel = new QLabel(dashboardFrame);
        tableSeatsLabel->setObjectName("tableSeatsLabel");

        horizontalLayout_3->addWidget(tableSeatsLabel);

        tableSeatsProgressBar = new QProgressBar(dashboardFrame);
        tableSeatsProgressBar->setObjectName("tableSeatsProgressBar");
        tableSeatsProgressBar->setValue(80);

        horizontalLayout_3->addWidget(tableSeatsProgressBar);

        clientMoodLabel = new QLabel(dashboardFrame);
        clientMoodLabel->setObjectName("clientMoodLabel");

        horizontalLayout_3->addWidget(clientMoodLabel);

        clientMoodProgressBar = new QProgressBar(dashboardFrame);
        clientMoodProgressBar->setObjectName("clientMoodProgressBar");
        clientMoodProgressBar->setValue(50);

        horizontalLayout_3->addWidget(clientMoodProgressBar);


        verticalLayout->addWidget(dashboardFrame);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Projet", nullptr));
        stratButton->setText(QString());
        pauseButton->setText(QString());
        stopButton->setText(QString());
        accelButton->setText(QString());
        timeButton->setText(QCoreApplication::translate("MainWindow", "Heure : 00 00", nullptr));
        alertButton->setText(QString());
        livraisonButton->setText(QString());
        paramButton->setText(QString());
        stockInfoTextBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:12px; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">Niveaux de stock:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">- Ingr\303\251dient 1: 50</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0"
                        "px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">- Ingr\303\251dient 2: 30</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">- Ingr\303\251dient 3: 20</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Commandes", nullptr));

        const bool __sortingEnabled = orderList->isSortingEnabled();
        orderList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = orderList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "Nouvel \303\251l\303\251ment", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = orderList->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nouvel \303\251l\303\251ment", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = orderList->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("MainWindow", "Nouvel \303\251l\303\251ment", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = orderList->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("MainWindow", "Nouvel \303\251l\303\251ment", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = orderList->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("MainWindow", "Nouvel \303\251l\303\251ment", nullptr));
        orderList->setSortingEnabled(__sortingEnabled);

        diningAreaLabel->setText(QCoreApplication::translate("MainWindow", "Salle de restauration", nullptr));
        kitchenAreaLabel->setText(QCoreApplication::translate("MainWindow", "Cuisine", nullptr));
        customerMoodButton->setText(QCoreApplication::translate("MainWindow", "Menu du restaurant", nullptr));

        const bool __sortingEnabled1 = menuListWidget->isSortingEnabled();
        menuListWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem5 = menuListWidget->item(0);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("MainWindow", "Salade", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = menuListWidget->item(1);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("MainWindow", "Glace avec Creme", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = menuListWidget->item(2);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("MainWindow", "Jus de raison", nullptr));
        menuListWidget->setSortingEnabled(__sortingEnabled1);

        tableInfoTextBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:12px; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">Infos tables:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">- Total tables: 20</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-blo"
                        "ck-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">- Tables occup\303\251es: 10</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">- Tables disponibles: 10</span></p></body></html>", nullptr));
        customerInfoTextBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:12px; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">Infos clients:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">- Total clients: 50</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-b"
                        "lock-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">- Clients en attente: 5</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt;\">- Clients servis: 45</span></p></body></html>", nullptr));
        stockLevelsLabel->setText(QCoreApplication::translate("MainWindow", "Niveaux de stock", nullptr));
        tableSeatsLabel->setText(QCoreApplication::translate("MainWindow", "Places \303\240 table", nullptr));
        clientMoodLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\231\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
