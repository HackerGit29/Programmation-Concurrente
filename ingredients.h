#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#endif // INGREDIENTS_H
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>

class Ingredient : public QObject
{
    Q_OBJECT

public:
    explicit Ingredient(QObject *parent = nullptr)
        : QObject(parent) {}

    // Signal à émettre lorsqu'il y a une mise à jour
signals:
    void dataChanged();

public slots:
    void addIngredients() {
        // Exemple de modification dans la base de données
        QSqlQuery query;
        query.exec("UPDATE ingredients SET quantite = quantite + 100");

        // Emettre un signal pour notifier la modification
        emit dataChanged();
    }

    void removeIngredient(int id) {
        // Exemple de suppression d'un ingrédient
        QSqlQuery query;
        query.prepare("DELETE FROM ingredients WHERE ingredient_id = :id");
        query.bindValue(":id", id);
        if (query.exec()) {
            emit dataChanged(); // Notifier que les données ont changé
        } else {
            qDebug() << "Erreur suppression : " << query.lastError().text();
        }
    }
};
