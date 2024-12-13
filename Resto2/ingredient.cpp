#include "ingredient.h"

// Constructeur
Ingredient::Ingredient(int id, const QString &name, int quantity, const QString &dishName)
    : id(id), name(name), quantity(quantity), dishName(dishName) {}

// Accesseurs
int Ingredient::getId() const {
    return id;
}

QString Ingredient::getName() const {
    return name;
}

int Ingredient::getQuantity() const {
    return quantity;
}

QString Ingredient::getDishName() const {
    return dishName;
}

// Méthode pour récupérer tous les ingrédients
QList<Ingredient> Ingredient::getAllIngredients() {
    QList<Ingredient> ingredientList;

    // Requête pour récupérer les données des ingrédients
    QSqlQuery query("SELECT ingredient_id, nom, quantite, dish_name FROM ingredients");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des ingrédients:" << query.lastError().text();
        return ingredientList;
    }

    // Parcours des résultats de la requête
    while (query.next()) {
        int id = query.value(0).toInt();                // Récupération de l'ID
        QString name = query.value(1).toString();       // Nom de l'ingrédient
        int quantity = query.value(2).toInt();          // Quantité disponible
        QString dishName = query.value(3).toString();   // Nom du plat associé

        // Création d'un objet Ingredient et ajout à la liste
        ingredientList.append(Ingredient(id, name, quantity, dishName));
    }

    return ingredientList;
}

// Méthode pour mettre à jour la quantité d'un ingrédient
void Ingredient::updateQuantity(int ingredientId, int quantity) {
    QSqlQuery query;

    // Préparation de la requête
    query.prepare("UPDATE ingredients SET quantite = quantite - :quantity WHERE ingredient_id = :ingredientId");
    query.bindValue(":quantity", quantity);
    query.bindValue(":ingredientId", ingredientId);

    // Exécution de la requête
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de la quantité de l'ingrédient:" << query.lastError().text();
    }
}
