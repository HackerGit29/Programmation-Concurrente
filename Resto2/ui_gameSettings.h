/********************************************************************************
** Form generated from reading UI file 'gameSettings.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESETTINGS_H
#define UI_GAMESETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GameSettings
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QFrame *settingsFrame;
    QFormLayout *formLayout;
    QLabel *startTimeLabel;
    QTimeEdit *startTimeEdit;
    QLabel *groupSizeLabel;
    QComboBox *groupSizeComboBox;
    QLabel *simulationSpeedLabel;
    QComboBox *comboBox;
    QFrame *buttonsFrame;
    QHBoxLayout *horizontalLayout;
    QPushButton *applyButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *GameSettings)
    {
        if (GameSettings->objectName().isEmpty())
            GameSettings->setObjectName("GameSettings");
        GameSettings->resize(400, 300);
        GameSettings->setStyleSheet(QString::fromUtf8("/* Background principal */\n"
"QWidget {\n"
"    background-color: #1e1e2e;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"/* Boutons */\n"
"QPushButton {\n"
"    background-color: #3a3a5f;\n"
"    selection-color: red;\n"
"    border: 2px solid #5e5edc;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    color: white;\n"
"    font: bold 14px \"Segoe UI\";\n"
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
"    background-color: #5e5edc;\n"
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
"\n"
"/* SpinBox */\n"
"QSpinBox {\n"
"    background-color: #2e2e3e;\n"
"    border: 2px solid #5e5edc;\n"
"    border-radius: 5px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* TimeEdit */\n"
"QTimeEdit {\n"
"    background-color: #2e2e3e;\n"
"    border: 2px solid #5e5edc;\n"
"    border-radius: 5px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* CheckBox */\n"
"QCheckBox {\n"
"    color: white;\n"
"    spacing: 10px;\n"
"}\n"
"\n"
"/* ComboBox */\n"
"QComboBox {\n"
"    background-color: #2e2e3e;\n"
"    border: 2px solid #5e5edc;\n"
"    border-radius: 5px;\n"
"    color: white;\n"
"    padding: 5p"
                        "x;\n"
"}\n"
"\n"
"/* Slider */\n"
"QSlider::groove:horizontal {\n"
"    border: 1px solid #5e5edc;\n"
"    height: 8px;\n"
"    background: #2e2e3e;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: #5e5edc;\n"
"    border: 1px solid #5e5edc;\n"
"    width: 18px;\n"
"    margin: -8px 0;\n"
"    border-radius: 9px;\n"
"}\n"
"\n"
"/* Toggle Button */\n"
"QCheckBox::indicator:checked {\n"
"    image: url(:/images/toggle_on.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked {\n"
"    image: url(:/images/toggle_off.png);\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(GameSettings);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(GameSettings);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        settingsFrame = new QFrame(GameSettings);
        settingsFrame->setObjectName("settingsFrame");
        settingsFrame->setFrameShape(QFrame::Shape::StyledPanel);
        settingsFrame->setFrameShadow(QFrame::Shadow::Raised);
        formLayout = new QFormLayout(settingsFrame);
        formLayout->setObjectName("formLayout");
        startTimeLabel = new QLabel(settingsFrame);
        startTimeLabel->setObjectName("startTimeLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, startTimeLabel);

        startTimeEdit = new QTimeEdit(settingsFrame);
        startTimeEdit->setObjectName("startTimeEdit");
        startTimeEdit->setTime(QTime(0, 0, 0));

        formLayout->setWidget(0, QFormLayout::FieldRole, startTimeEdit);

        groupSizeLabel = new QLabel(settingsFrame);
        groupSizeLabel->setObjectName("groupSizeLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, groupSizeLabel);

        groupSizeComboBox = new QComboBox(settingsFrame);
        groupSizeComboBox->addItem(QString());
        groupSizeComboBox->addItem(QString());
        groupSizeComboBox->setObjectName("groupSizeComboBox");

        formLayout->setWidget(1, QFormLayout::FieldRole, groupSizeComboBox);

        simulationSpeedLabel = new QLabel(settingsFrame);
        simulationSpeedLabel->setObjectName("simulationSpeedLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, simulationSpeedLabel);

        comboBox = new QComboBox(settingsFrame);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        formLayout->setWidget(3, QFormLayout::FieldRole, comboBox);


        verticalLayout->addWidget(settingsFrame);

        buttonsFrame = new QFrame(GameSettings);
        buttonsFrame->setObjectName("buttonsFrame");
        buttonsFrame->setFrameShape(QFrame::Shape::StyledPanel);
        buttonsFrame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(buttonsFrame);
        horizontalLayout->setObjectName("horizontalLayout");
        applyButton = new QPushButton(buttonsFrame);
        applyButton->setObjectName("applyButton");

        horizontalLayout->addWidget(applyButton);

        cancelButton = new QPushButton(buttonsFrame);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addWidget(buttonsFrame);


        retranslateUi(GameSettings);

        QMetaObject::connectSlotsByName(GameSettings);
    } // setupUi

    void retranslateUi(QDialog *GameSettings)
    {
        GameSettings->setWindowTitle(QCoreApplication::translate("GameSettings", "Param\303\250tres de Simulation", nullptr));
        titleLabel->setText(QCoreApplication::translate("GameSettings", "Param\303\250tres de Simulation", nullptr));
        startTimeLabel->setText(QCoreApplication::translate("GameSettings", "Heure de d\303\251marrage :", nullptr));
        groupSizeLabel->setText(QCoreApplication::translate("GameSettings", "Maximum de personnes par groupe :", nullptr));
        groupSizeComboBox->setItemText(0, QCoreApplication::translate("GameSettings", "4", nullptr));
        groupSizeComboBox->setItemText(1, QCoreApplication::translate("GameSettings", "8", nullptr));

        groupSizeComboBox->setCurrentText(QCoreApplication::translate("GameSettings", "4", nullptr));
        simulationSpeedLabel->setText(QCoreApplication::translate("GameSettings", "Vitesse de simulation :", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("GameSettings", "Normal", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("GameSettings", "2", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("GameSettings", "3", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("GameSettings", "4", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("GameSettings", "5", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("GameSettings", "6", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("GameSettings", "7", nullptr));

        applyButton->setText(QCoreApplication::translate("GameSettings", "Appliquer", nullptr));
        cancelButton->setText(QCoreApplication::translate("GameSettings", "Annuler", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameSettings: public Ui_GameSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESETTINGS_H
