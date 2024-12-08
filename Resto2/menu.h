#ifndef MENU_H
#define MENU_H

#include <QString>

class Menu {
public:
    explicit Menu(const QString &name);
    QString getName() const;

private:
    QString name;
};

#endif // MENU_H
