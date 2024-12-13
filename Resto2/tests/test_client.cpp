#include <QtTest/QtTest>
#include "../client.h"

class TestClient : public QObject {
    Q_OBJECT

private slots:
    void testGettersAndSetters();
    void testSignals();
};

void TestClient::testGettersAndSetters() {
    Client client(1, 4, nullptr);

    // Test des accesseurs
    QCOMPARE(client.getId(), 1);
    QCOMPARE(client.getGroupSize(), 4);
    QCOMPARE(client.getIsSeated(), false);
    QCOMPARE(client.getHasOrdered(), false);

    // Test des mutateurs
    client.setSeated(true);
    QCOMPARE(client.getIsSeated(), true);

    client.setHasOrdered(true);
    QCOMPARE(client.getHasOrdered(), true);

    client.setConsuming(true);
    QCOMPARE(client.getIsConsuming(), true);
}

void TestClient::testSignals() {
    Client client(2, 3, nullptr);
    QSignalSpy orderSpy(&client, &Client::orderPlaced);
    QSignalSpy leaveSpy(&client, &Client::clientLeft);

    emit client.orderPlaced(3);
    emit client.clientLeft();

    QCOMPARE(orderSpy.count(), 1);
    QCOMPARE(leaveSpy.count(), 1);
}

QTEST_MAIN(TestClient)
#include "test_client.moc"
