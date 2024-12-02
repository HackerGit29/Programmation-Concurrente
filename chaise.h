#ifndef CHAISE_H
#define CHAISE_H

#include <QString>

class Chaise {
public:
    Chaise(int id, int x, int y, const QString &imagePath);

    int getId() const;
    int getX() const;
    int getY() const;
    QString getImagePath() const;

    void setX(int x);
    void setY(int y);
    void setImagePath(const QString &imagePath);

private:
    int id;
    int x;
    int y;
    QString imagePath;
};

#endif // CHAISE_H
