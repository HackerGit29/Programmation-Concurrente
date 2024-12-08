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

    QTime getStartTime() const;        // Récupère l'heure de début
    int getGroupSize() const;          // Récupère la taille du groupe
    int getSimulationSpeed() const;    // Récupère la vitesse de simulation
    bool isSoundEnabled() const;       // Vérifie si le son est activé
    QPushButton* getApplyButton() const; // Retourne un pointeur sur le bouton Apply

private:
    Settings *ui;
};

#endif // SETTINGS_H
