#ifndef STOCKWINDOW_H
#define STOCKWINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include "ingredientfactory.h"

namespace Ui {
class stockWindow;
}

class stockWindow : public QDialog {
    Q_OBJECT

public:
    explicit stockWindow(QWidget *parent = nullptr);
    ~stockWindow();

    void setDatabase(QSqlDatabase db); // Pour connecter la base de données

private slots:
    void onCommandButtonClicked(); // Slot pour le bouton "Commander"

private:
    Ui::stockWindow *ui;
    QSqlDatabase database; // Instance de la base de données

    void insertIngredientIntoDatabase(Ingredient *ingredient); // Méthode pour insérer dans la base
};

#endif // STOCKWINDOW_H
