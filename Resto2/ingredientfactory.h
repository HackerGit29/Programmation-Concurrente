#ifndef INGREDIENTFACTORY_H
#define INGREDIENTFACTORY_H

#include "ingredient.h"

class IngredientFactory {
public:
    static Ingredient* createIngredient(int id, const QString &name, int quantity, const QString &dishName);
};

#endif // INGREDIENTFACTORY_H
