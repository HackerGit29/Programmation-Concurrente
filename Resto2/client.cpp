#include "client.h"
#include <QThread>
#include <QDebug>

Client::Client(int id, int groupSize, QObject* parent)
    : QObject(parent), id(id), groupSize(groupSize), isSeated(false), hasOrdered(false), isConsuming(false), clientImage(nullptr), scene(nullptr), timeline(nullptr), timelineDuration(0) {


    // Chargement d'une image PNG représentant le client
    QPixmap pixmap(":/images/client.png"); // Chemin à adapter selon votre projet

    // Création d'un QGraphicsPixmapItem pour représenter visuellement le client
    clientImage = new QGraphicsPixmapItem(pixmap);
    clientImage->setTransformationMode(Qt::SmoothTransformation);
}

int Client::getId() const {
    return id;
}

int Client::getGroupSize() const {
    return groupSize;
}

bool Client::getIsSeated() const {
    return isSeated;
}

bool Client::getHasOrdered() const {
    return hasOrdered;
}

bool Client::getIsConsuming() const {
    return isConsuming;
}

void Client::setSeated(bool seated) {
    isSeated = seated;
}

void Client::setHasOrdered(bool ordered) {
    hasOrdered = ordered;
}

void Client::setConsuming(bool consuming) {
    isConsuming = consuming;
}

void Client::moveToPosition(const QPointF& position) {
    if (clientImage) {
        clientImage->setPos(position);
    }
}

void Client::removeFromScene() {
    if (clientImage && scene) {
        scene->removeItem(clientImage);
    }
}

void Client::startTimeline() {
    if (!timeline) {
        timeline = new QThread(this);
        connect(timeline, &QThread::started, this, &Client::runTimeline);
        timeline->start();
    }
}

void Client::pauseTimeline() {
    if (timeline) {
        timeline->requestInterruption();
        timeline->wait();
    }
}

void Client::stopTimeline() {
    if (timeline) {
        timeline->terminate();
        timeline->wait();
        delete timeline;
        timeline = nullptr;
    }
}

void Client::setDuration(int duration) {
    timelineDuration = duration;
}

int Client::duration() const {
    return timelineDuration;
}

void Client::runTimeline() {
    QThread::sleep(timelineDuration);
    emit clientLeft();
}
