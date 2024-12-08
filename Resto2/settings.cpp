#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QTime>
#include <QPushButton>

class Settings : public QDialog
{
    Q_OBJECT

signals:
    void applyButtonClicked();

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    QTime getStartTime() const;
    int getGroupSize() const;
    int getSimulationSpeed() const;
    bool isSoundEnabled() const;
    QPushButton* getApplyButton() const;

private:
    Settings *ui; // Cette déclaration correspond à la classe définie dans ui_settings.h
};

#endif // SETTINGS_H
