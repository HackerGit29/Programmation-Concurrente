#include "chaise.h"

Chaise::Chaise(int id, int x, int y, const QString &imagePath)
    : id(id), x(x), y(y), imagePath(imagePath) {}

int Chaise::getId() const { return id; }
int Chaise::getX() const { return x; }
int Chaise::getY() const { return y; }
QString Chaise::getImagePath() const { return imagePath; }

void Chaise::setX(int x) { this->x = x; }
void Chaise::setY(int y) { this->y = y; }
void Chaise::setImagePath(const QString &imagePath) { this->imagePath = imagePath; }
