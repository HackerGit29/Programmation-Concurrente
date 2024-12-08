#include "gameSettings.h"
#include "ui_gameSettings.h"

GameSettings::GameSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameSettings) {
    ui->setupUi(this);
}

GameSettings::~GameSettings() {
    delete ui;
}

int GameSettings::getGroupSizeLimit() const {
    return ui->groupSizeComboBox->currentText().toInt();
}

int GameSettings::getSimulationSpeed() const {
    QString speed = ui->comboBox->currentText();
    if (speed == "Normal") {
        return 1;
    }
    return speed.toInt();
}

QTime GameSettings::getStartTime() const {
    return ui->startTimeEdit->time();
}
