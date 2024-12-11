#ifndef CLIENT_H
#define CLIENT_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QObject>
#include <QString>
#include <QThread>

class Client : public QObject {
    Q_OBJECT

public:
    explicit Client(int id, int groupSize, QObject* parent = nullptr);

    // Accesseurs
    int getId() const;
    int getGroupSize() const;
    bool getIsSeated() const;
    bool getHasOrdered() const;
    bool getIsConsuming() const;

    // Mutateurs
    void setSeated(bool seated);
    void setHasOrdered(bool ordered);
    void setConsuming(bool consuming);
    void moveToPosition(const QPointF& position);
    void removeFromScene();

    // Méthodes pour gérer les threads
    void startTimeline();
    void pauseTimeline();
    void stopTimeline();
    void setDuration(int duration);
    int duration() const;

signals:
    void orderPlaced(int groupSize);
    void mealFinished();
    void clientLeft();

private:
    int id;             // Son ID
    int groupSize;      // Nombre de personnes dans le groupe
    bool isSeated;      // Si le client est assis
    bool hasOrdered;    // Si le client a passé sa commande
    bool isConsuming;   // Si le client est en train de manger
    QGraphicsPixmapItem* clientImage; // Représentation graphique
    QGraphicsScene* scene;           // Scène où le client est affiché
    QThread* timeline;               // Thread pour gérer la timeline du client
    int timelineDuration;            // Durée de la timeline en secondes

    void runTimeline();
};

#endif // CLIENT_H
