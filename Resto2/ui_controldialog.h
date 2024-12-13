/********************************************************************************
** Form generated from reading UI file 'controldialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLDIALOG_H
#define UI_CONTROLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ControlDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QHBoxLayout *dashboardLayout;
    QFrame *clientsCard;
    QVBoxLayout *clientsCardLayout;
    QLabel *clientsCardTitle;
    QLabel *clientsCardValue;
    QFrame *tablesCard;
    QVBoxLayout *tablesCardLayout;
    QLabel *tablesCardTitle;
    QLabel *tablesCardValue;
    QFrame *staffCard;
    QVBoxLayout *staffCardLayout;
    QLabel *staffCardTitle;
    QLabel *staffCardValue;
    QHBoxLayout *statusLayout;
    QTableView *clientsTableView;
    QTableView *tablesTableView;
    QVBoxLayout *ingredientsLayout;
    QLabel *progressLabel;
    QTableView *alertsListWidget;
    QVBoxLayout *alertsLayout;

    void setupUi(QDialog *ControlDialog)
    {
        if (ControlDialog->objectName().isEmpty())
            ControlDialog->setObjectName("ControlDialog");
        ControlDialog->resize(600, 600);
        ControlDialog->setStyleSheet(QString::fromUtf8("/* Background principal */\n"
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
"    background-color: #3a3a5f;\n"
"    border: 2px solid #5e5edc;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #7366ff;\n"
"    border-color: #8080ff;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #282850;\n"
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
"    c"
                        "olor: white;\n"
"    font: bold 12px \"Segoe UI\";\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background-color: #7366ff;\n"
"    border-radius: 5px;\n"
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
"\n"
"/* Table Views */\n"
"QTableView {\n"
"    border: 2px solid #3a3a5f;\n"
"    border-radius: 10px;\n"
"    background-color: #2e2e3e;\n"
"    color: white;\n"
"    font: 12px \"Segoe UI\";\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QTableView::item {\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QTableView::item:selected {\n"
"    background-color: #7366ff;\n"
"    color: white;\n"
"}\n"
"\n"
"/* List Widgets */\n"
"QListWidget {\n"
"    border: 2px solid #3a3a5f;\n"
"    border-radius: 10px;\n"
"    background-color: #2e2e3e;\n"
"    color: white;\n"
"    font: 12px \"Segoe UI\";\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QListWidget::ite"
                        "m {\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background-color: #7366ff;\n"
"    color: white;\n"
"}\n"
"\n"
"/* Dialogs */\n"
"QDialog {\n"
"    background-color: #1e1e2e;\n"
"    color: #ffffff;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"/* Scroll Bars */\n"
"QScrollBar:vertical {\n"
"    background: #2e2e3e;\n"
"    width: 12px;\n"
"    margin: 0px 0px 0px 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #7366ff;\n"
"    min-height: 20px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"    background: #2e2e3e;\n"
"    height: 12px;\n"
"    margin: 0px 0px 0px 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"    background: #7366ff;\n"
"    min-width: 20px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {\n"
"    width: 0px;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(ControlDialog);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(ControlDialog);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setBold(true);
        font.setItalic(false);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        dashboardLayout = new QHBoxLayout();
        dashboardLayout->setObjectName("dashboardLayout");
        clientsCard = new QFrame(ControlDialog);
        clientsCard->setObjectName("clientsCard");
        clientsCard->setFrameShape(QFrame::Shape::StyledPanel);
        clientsCard->setFrameShadow(QFrame::Shadow::Raised);
        clientsCardLayout = new QVBoxLayout(clientsCard);
        clientsCardLayout->setObjectName("clientsCardLayout");
        clientsCardTitle = new QLabel(clientsCard);
        clientsCardTitle->setObjectName("clientsCardTitle");
        clientsCardTitle->setFont(font);
        clientsCardTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        clientsCardLayout->addWidget(clientsCardTitle);

        clientsCardValue = new QLabel(clientsCard);
        clientsCardValue->setObjectName("clientsCardValue");
        clientsCardValue->setFont(font);
        clientsCardValue->setAlignment(Qt::AlignmentFlag::AlignCenter);

        clientsCardLayout->addWidget(clientsCardValue);


        dashboardLayout->addWidget(clientsCard);

        tablesCard = new QFrame(ControlDialog);
        tablesCard->setObjectName("tablesCard");
        tablesCard->setFrameShape(QFrame::Shape::StyledPanel);
        tablesCard->setFrameShadow(QFrame::Shadow::Raised);
        tablesCardLayout = new QVBoxLayout(tablesCard);
        tablesCardLayout->setObjectName("tablesCardLayout");
        tablesCardTitle = new QLabel(tablesCard);
        tablesCardTitle->setObjectName("tablesCardTitle");
        tablesCardTitle->setFont(font);
        tablesCardTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        tablesCardLayout->addWidget(tablesCardTitle);

        tablesCardValue = new QLabel(tablesCard);
        tablesCardValue->setObjectName("tablesCardValue");
        tablesCardValue->setFont(font);
        tablesCardValue->setAlignment(Qt::AlignmentFlag::AlignCenter);

        tablesCardLayout->addWidget(tablesCardValue);


        dashboardLayout->addWidget(tablesCard);

        staffCard = new QFrame(ControlDialog);
        staffCard->setObjectName("staffCard");
        staffCard->setFrameShape(QFrame::Shape::StyledPanel);
        staffCard->setFrameShadow(QFrame::Shadow::Raised);
        staffCardLayout = new QVBoxLayout(staffCard);
        staffCardLayout->setObjectName("staffCardLayout");
        staffCardTitle = new QLabel(staffCard);
        staffCardTitle->setObjectName("staffCardTitle");
        staffCardTitle->setFont(font);
        staffCardTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        staffCardLayout->addWidget(staffCardTitle);

        staffCardValue = new QLabel(staffCard);
        staffCardValue->setObjectName("staffCardValue");
        staffCardValue->setFont(font);
        staffCardValue->setAlignment(Qt::AlignmentFlag::AlignCenter);

        staffCardLayout->addWidget(staffCardValue);


        dashboardLayout->addWidget(staffCard);


        verticalLayout->addLayout(dashboardLayout);

        statusLayout = new QHBoxLayout();
        statusLayout->setObjectName("statusLayout");
        clientsTableView = new QTableView(ControlDialog);
        clientsTableView->setObjectName("clientsTableView");

        statusLayout->addWidget(clientsTableView);

        tablesTableView = new QTableView(ControlDialog);
        tablesTableView->setObjectName("tablesTableView");

        statusLayout->addWidget(tablesTableView);


        verticalLayout->addLayout(statusLayout);

        ingredientsLayout = new QVBoxLayout();
        ingredientsLayout->setObjectName("ingredientsLayout");
        progressLabel = new QLabel(ControlDialog);
        progressLabel->setObjectName("progressLabel");

        ingredientsLayout->addWidget(progressLabel);

        alertsListWidget = new QTableView(ControlDialog);
        alertsListWidget->setObjectName("alertsListWidget");

        ingredientsLayout->addWidget(alertsListWidget);


        verticalLayout->addLayout(ingredientsLayout);

        alertsLayout = new QVBoxLayout();
        alertsLayout->setObjectName("alertsLayout");

        verticalLayout->addLayout(alertsLayout);


        retranslateUi(ControlDialog);

        QMetaObject::connectSlotsByName(ControlDialog);
    } // setupUi

    void retranslateUi(QDialog *ControlDialog)
    {
        ControlDialog->setWindowTitle(QCoreApplication::translate("ControlDialog", "Contr\303\264le de l'\303\251tat du restaurant", nullptr));
        titleLabel->setText(QCoreApplication::translate("ControlDialog", "\303\211tat des ressources et des clients", nullptr));
        clientsCardTitle->setText(QCoreApplication::translate("ControlDialog", "Clients", nullptr));
        clientsCardValue->setText(QCoreApplication::translate("ControlDialog", "0", nullptr));
        tablesCardTitle->setText(QCoreApplication::translate("ControlDialog", "Tables", nullptr));
        tablesCardValue->setText(QCoreApplication::translate("ControlDialog", "0", nullptr));
        staffCardTitle->setText(QCoreApplication::translate("ControlDialog", "Personnel", nullptr));
        staffCardValue->setText(QCoreApplication::translate("ControlDialog", "0", nullptr));
#if QT_CONFIG(tooltip)
        clientsTableView->setToolTip(QCoreApplication::translate("ControlDialog", "Liste des clients et leur \303\251tat", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        tablesTableView->setToolTip(QCoreApplication::translate("ControlDialog", "Liste des tables et leur occupation", nullptr));
#endif // QT_CONFIG(tooltip)
        progressLabel->setText(QCoreApplication::translate("ControlDialog", "Historique des alertes", nullptr));
#if QT_CONFIG(tooltip)
        alertsListWidget->setToolTip(QCoreApplication::translate("ControlDialog", "Liste des ingr\303\251dients disponibles", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class ControlDialog: public Ui_ControlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLDIALOG_H
