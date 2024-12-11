#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QString>
#include <QDate>
#include <QList>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

class Ingredient {
public:
    // Constructeur
    Ingredient(int id, const QString &name, int quantity, const QString &dishName);

    // Accesseurs
    int getId() const;
    QString getName() const;
    int getQuantity() const;
    QString getDishName() const;

    // Méthodes statiques
    static QList<Ingredient> getAllIngredients();
    static void updateQuantity(int ingredientId, int quantity);

private:
    // Attributs
    int id;
    QString name;          // Nom de l'ingrédient
    int quantity;          // Quantité disponible
    QString dishName;      // Nom du plat associé
};

#endif // INGREDIENT_H
