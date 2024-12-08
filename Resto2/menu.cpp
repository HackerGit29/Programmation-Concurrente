#include "menu.h"

Menu::Menu(const QString &name) : name(name) {}

QString Menu::getName() const {
    return name;
}
