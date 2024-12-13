/********************************************************************************
** Form generated from reading UI file 'stockwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOCKWINDOW_H
#define UI_STOCKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stockWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *imageLabel;
    QVBoxLayout *formLayout;
    QWidget *formWidget;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *nomDeLIngrDientLabel;
    QLineEdit *nomDeLIngrDientLineEdit;
    QLabel *dishNameLabel;
    QLineEdit *dishNameLineEdit;
    QLabel *typeLabel;
    QLineEdit *quantitLineEdit;
    QPushButton *commandButton;

    void setupUi(QDialog *stockWindow)
    {
        if (stockWindow->objectName().isEmpty())
            stockWindow->setObjectName("stockWindow");
        stockWindow->resize(647, 602);
        horizontalLayout = new QHBoxLayout(stockWindow);
        horizontalLayout->setObjectName("horizontalLayout");
        imageLabel = new QLabel(stockWindow);
        imageLabel->setObjectName("imageLabel");
        imageLabel->setMinimumSize(QSize(369, 200));
        imageLabel->setStyleSheet(QString::fromUtf8("background-image: url(:img/market.jpeg);"));
        imageLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/livreur_cartons.png")));
        imageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(imageLabel);

        formLayout = new QVBoxLayout();
        formLayout->setObjectName("formLayout");
        formWidget = new QWidget(stockWindow);
        formWidget->setObjectName("formWidget");
        formWidget->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"  border-radius: 8px;\n"
"  border: 1px solid #e0e4e7;\n"
"  padding: 5px 15px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"  border: 1px solid #d0e3ff;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"  color: #767e89;\n"
"}\n"
"\n"
"QComboBox {\n"
"  border-radius: 8px;\n"
"  border: 1px solid #e0e4e7;\n"
"  padding: 5px 15px;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"  border: 1px solid #d0e3ff;\n"
"}"));
        formLayout_2 = new QFormLayout(formWidget);
        formLayout_2->setObjectName("formLayout_2");
        label = new QLabel(formWidget);
        label->setObjectName("label");

        formLayout_2->setWidget(0, QFormLayout::SpanningRole, label);

        nomDeLIngrDientLabel = new QLabel(formWidget);
        nomDeLIngrDientLabel->setObjectName("nomDeLIngrDientLabel");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, nomDeLIngrDientLabel);

        nomDeLIngrDientLineEdit = new QLineEdit(formWidget);
        nomDeLIngrDientLineEdit->setObjectName("nomDeLIngrDientLineEdit");

        formLayout_2->setWidget(1, QFormLayout::FieldRole, nomDeLIngrDientLineEdit);

        dishNameLabel = new QLabel(formWidget);
        dishNameLabel->setObjectName("dishNameLabel");

        formLayout_2->setWidget(2, QFormLayout::LabelRole, dishNameLabel);

        dishNameLineEdit = new QLineEdit(formWidget);
        dishNameLineEdit->setObjectName("dishNameLineEdit");

        formLayout_2->setWidget(2, QFormLayout::FieldRole, dishNameLineEdit);

        typeLabel = new QLabel(formWidget);
        typeLabel->setObjectName("typeLabel");

        formLayout_2->setWidget(3, QFormLayout::LabelRole, typeLabel);

        quantitLineEdit = new QLineEdit(formWidget);
        quantitLineEdit->setObjectName("quantitLineEdit");

        formLayout_2->setWidget(3, QFormLayout::FieldRole, quantitLineEdit);


        formLayout->addWidget(formWidget);

        commandButton = new QPushButton(stockWindow);
        commandButton->setObjectName("commandButton");

        formLayout->addWidget(commandButton);


        horizontalLayout->addLayout(formLayout);


        retranslateUi(stockWindow);

        QMetaObject::connectSlotsByName(stockWindow);
    } // setupUi

    void retranslateUi(QDialog *stockWindow)
    {
        stockWindow->setWindowTitle(QCoreApplication::translate("stockWindow", "Gestion des Stocks", nullptr));
        label->setText(QCoreApplication::translate("stockWindow", "Approvisionner le restaurant", nullptr));
        nomDeLIngrDientLabel->setText(QCoreApplication::translate("stockWindow", "Nom de l'ingr\303\251dient", nullptr));
        dishNameLabel->setText(QCoreApplication::translate("stockWindow", "Recette", nullptr));
        typeLabel->setText(QCoreApplication::translate("stockWindow", "Quantit\303\251", nullptr));
        commandButton->setStyleSheet(QCoreApplication::translate("stockWindow", "\n"
"         QPushButton {\n"
"             background-color: #4CAF50;\n"
"             color: white;\n"
"             border-radius: 10px;\n"
"             padding: 10px;\n"
"         }\n"
"         QPushButton:hover {\n"
"             background-color: #45a049;\n"
"         }\n"
"        ", nullptr));
        commandButton->setText(QCoreApplication::translate("stockWindow", "Commander", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stockWindow: public Ui_stockWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOCKWINDOW_H
