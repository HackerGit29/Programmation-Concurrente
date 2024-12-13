#ifndef CONTROLDIALOG_H
#define CONTROLDIALOG_H

#include <QDialog>
#include "tablecontroller.h"
#include "employeecontroller.h"

namespace Ui {
class ControlDialog;
}

class ControlDialog : public QDialog {
    Q_OBJECT

public:
    explicit ControlDialog(QWidget *parent = nullptr);
    ~ControlDialog();

    void setTableController(TableController *controller);
    void setEmployeeController(EmployeeController *controller);
    void setClientCount(int count);

private slots:
    void updateCards();

private:
    Ui::ControlDialog *ui;

    TableController *tableController;
    EmployeeController *employeeController;
    int clientCount;

    void setupUI();
    void setupConnections();
};

#endif // CONTROLDIALOG_H
