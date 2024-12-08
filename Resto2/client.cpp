#include "client.h"

Client::Client(int id, int groupSize, QObject* parent)
    : QObject(parent), id(id),  groupSize(groupSize),isSeated(false), hasOrdered(false), isConsuming(false){
}

int Client::getGroupSize() const { return groupSize; }
int Client::getId() const { return id; }

bool Client::getIsSeated() const { return isSeated; }
bool Client::getHasOrdered() const { return hasOrdered; }
bool Client::getIsConsuming() const { return isConsuming; }

void Client::setSeated(bool seated) { isSeated = seated; }
void Client::setHasOrdered(bool ordered) { hasOrdered = ordered; }
void Client::setConsuming(bool consuming) { isConsuming = consuming; }


void Client::moveToPosition(const QPointF& position) {
    if (clientImage) {
        clientImage->setPos(position);
    }
}

void Client::removeFromScene() {
    if (clientImage) {
        scene->removeItem(clientImage);
        delete clientImage;
        clientImage = nullptr;
    }
}
