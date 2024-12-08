#include "stockwindow.h"
#include "ui_stockwindow.h"

StockWindow::StockWindow(QWidget *parent) :
    QMainWindow(parent), // Héritez de QMainWindow
    ui(new Ui::stockWindow) // Utilisez le nom correct de la classe générée par Qt Designer
{
    ui->setupUi(this);
}

StockWindow::~StockWindow()
{
    delete ui;
}
