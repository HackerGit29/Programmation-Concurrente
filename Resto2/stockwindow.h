#ifndef STOCKWINDOW_H
#define STOCKWINDOW_H

#include <QMainWindow>


namespace Ui {
class stockWindow; // Utilisez le nom correct de la classe générée par Qt Designer
}

class StockWindow : public QMainWindow // Héritez de QMainWindow
{
    Q_OBJECT

public:
    explicit StockWindow(QWidget *parent = nullptr);
    ~StockWindow();

private:
    Ui::stockWindow *ui; // Utilisez le nom correct de la classe générée par Qt Designer
};

#endif // STOCKWINDOW_H
