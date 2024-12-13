#include "controldialog.h"
#include "ui_controldialog.h"

ControlDialog::ControlDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::ControlDialog),
    tableController(nullptr),
    employeeController(nullptr),
    clientCount(0) {
    ui->setupUi(this);
    setupUI();
    setupConnections();
}

ControlDialog::~ControlDialog() {
    delete ui;
}

void ControlDialog::setTableController(TableController *controller) {
    tableController = controller;
    updateCards();
}

void ControlDialog::setEmployeeController(EmployeeController *controller) {
    employeeController = controller;
    updateCards();
}

void ControlDialog::setClientCount(int count) {
    clientCount = count;
    updateCards();
}

void ControlDialog::setupUI() {
    ui->clientsCardValue->setText("0");
    ui->tablesCardValue->setText("0");
    ui->staffCardValue->setText("0");
}

void ControlDialog::setupConnections() {
    // Mise à jour automatique si les données changent
    if (tableController) {
        connect(tableController, &TableController::tableUpdated, this, &ControlDialog::updateCards);
    }
    if (employeeController) {
        connect(employeeController, &EmployeeController::employeeListChanged, this, &ControlDialog::updateCards);
    }
}

void ControlDialog::updateCards() {
    if (tableController) {
        ui->tablesCardValue->setText(QString::number(tableController->getTableCount()));
    }

    if (employeeController) {
        ui->staffCardValue->setText(QString::number(employeeController->getEmployeeCount()));
    }

    ui->clientsCardValue->setText(QString::number(clientCount));
}
