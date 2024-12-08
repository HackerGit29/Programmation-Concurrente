#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H


#include <QDialog>

namespace Ui {
class GameSettings;
}

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
