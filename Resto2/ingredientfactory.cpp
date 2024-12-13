#include "ingredientfactory.h"

// Implémentation de la méthode pour créer un ingrédient
Ingredient* IngredientFactory::createIngredient(int id, const QString &name, int quantity, const QString &dishName) {
    return new Ingredient(id, name, quantity, dishName);
}
