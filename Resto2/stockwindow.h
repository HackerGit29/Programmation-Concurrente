#ifndef STOCKWINDOW_H
#define STOCKWINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include "ingredient.h"

namespace Ui {
class stockWindow;
}

class stockWindow : public QDialog {
    Q_OBJECT

public:
    explicit stockWindow(QWidget *parent = nullptr);
    ~stockWindow();

    void setDatabase(QSqlDatabase db);

private slots:
    void onCommandButtonClicked();

private:
    void insertIngredientIntoDatabase(Ingredient *ingredient);

    Ui::stockWindow *ui;
    QSqlDatabase database;
};

#endif // STOCKWINDOW_H
