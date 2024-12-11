#include "stockwindow.h"
#include "ui_stockwindow.h"
#include "ingredientfactory.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

stockWindow::stockWindow(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::stockWindow) {
    ui->setupUi(this);

    // Connecter le clic du bouton "Commander"
    connect(ui->commandButton, &QPushButton::clicked, this, &stockWindow::onCommandButtonClicked);
}

stockWindow::~stockWindow() {
    delete ui;
}

void stockWindow::setDatabase(QSqlDatabase db) {
    database = db;
}

void stockWindow::onCommandButtonClicked() {
    // Récupérer les données depuis les champs de saisie
    QString name = ui->nomDeLIngrDientLineEdit->text();
    int quantity = ui->quantitLineEdit->text().toInt();
    QString dishName = ui->dishNameLineEdit->text();

    if (name.isEmpty() || dishName.isEmpty() || quantity <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement.");
        return;
    }

    // Créer un ingrédient via la factory
    Ingredient *ingredient = IngredientFactory::createIngredient(-1, name, quantity, dishName);

    // Insérer dans la base de données
    insertIngredientIntoDatabase(ingredient);

    // Nettoyer les champs après insertion
    ui->nomDeLIngrDientLineEdit->clear();
    ui->quantitLineEdit->clear();
    ui->dishNameLineEdit->clear();

    delete ingredient;
}

void stockWindow::insertIngredientIntoDatabase(Ingredient *ingredient) {
    if (!database.isOpen()) {
        QMessageBox::critical(this, "Erreur", "La connexion à la base de données a échoué.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO ingredients (nom, quantite, dish_name) "
                  "VALUES (:nom, :quantite, :dish_name)");
    query.bindValue(":nom", ingredient->getName());
    query.bindValue(":quantite", ingredient->getQuantity());
    query.bindValue(":dish_name", ingredient->getDishName());

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "L'ingrédient a été ajouté avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter l'ingrédient dans la base de données : " + query.lastError().text());
    }
}
