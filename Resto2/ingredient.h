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
    Ingredient(int id, const QString &name, const QString &type, int quantity, const QDate &receptionDate, const QDate &expirationDate);

    int getId() const;
    QString getName() const;
    QString getType() const;
    int getQuantity() const;
    QDate getReceptionDate() const;
    QDate getExpirationDate() const;

    static QList<Ingredient> getAllIngredients();
    static void updateQuantity(int ingredientId, int quantity);

private:
    int id;
    QString name;
    QString type;
    int quantity;
    QDate receptionDate;
    QDate expirationDate;
};

#endif // INGREDIENT_H
