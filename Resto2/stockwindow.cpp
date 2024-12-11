#include "stockwindow.h"
#include "ui_stockwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDate>

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
    QString type = ui->typeComboBox->currentText();
    int quantity = ui->quantitLineEdit->text().toInt();
    QDate receptionDate = QDate::currentDate();
    QDate expirationDate = receptionDate.addDays(7); // Exemple : 7 jours de validité

    if (name.isEmpty() || type.isEmpty() || quantity <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement.");
        return;
    }

    // Créer un ingrédient via la factory
    Ingredient *ingredient = IngredientFactory::createIngredient(
        -1, name, type, quantity, receptionDate, expirationDate
        );

    // Insérer dans la base de données
    insertIngredientIntoDatabase(ingredient);

    // Nettoyer les champs après insertion
    ui->nomDeLIngrDientLineEdit->clear();
    ui->quantitLineEdit->clear();
    ui->typeComboBox->setCurrentIndex(0);

    delete ingredient;
}

void stockWindow::insertIngredientIntoDatabase(Ingredient *ingredient) {
    if (!database.isOpen()) {
        QMessageBox::critical(this, "Erreur", "La connexion à la base de données a échoué.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO ingredients (nom, type, quantite, date_reception, date_peremption) "
                  "VALUES (:nom, :type, :quantite, :date_reception, :date_peremption)");
    query.bindValue(":nom", ingredient->getName());
    query.bindValue(":type", ingredient->getType());
    query.bindValue(":quantite", ingredient->getQuantity());
    query.bindValue(":date_reception", ingredient->getReceptionDate());
    query.bindValue(":date_peremption", ingredient->getExpirationDate());

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "L'ingrédient a été ajouté avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter l'ingrédient dans la base de données.");
    }
}
