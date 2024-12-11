#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H


#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>


QT_BEGIN_NAMESPACE

namespace Ui {
class GameSettings;
}

QT_END_NAMESPACE


class GameSettings : public QDialog {
    Q_OBJECT

public:
    explicit GameSettings(QWidget *parent = nullptr);
    ~GameSettings();

    int getGroupSizeLimit() const;
    int getSimulationSpeed() const;
    QTime getStartTime() const;

private:
    Ui::GameSettings *ui;
};



#endif // GAMESETTINGS_H
