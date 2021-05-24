#ifndef BLESERVICEDECODER_H
#define BLESERVICEDECODER_H

#include <QObject>
#include <QBluetoothLocalDevice>
#include <QBluetoothAddress>
#include <QBluetoothUuid>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QTimer>

#include "BleMessage.h"

class BleServiceDecoder : public QObject
{
    Q_OBJECT
public:
    explicit BleServiceDecoder(QLowEnergyService* service, QBluetoothUuid characteristicUuid, QLowEnergyCharacteristic::PropertyType property, QByteArray writeValue=QByteArray::fromHex("0000"), QObject *parent = nullptr);

    void start();

    // data - pointer to the payload data. To handle this data, reinterpret_cast this to the appropriate BleMessage to access sections of bits.
    char* data;

signals:
    // Signal emitted when characteristic data is recieved from the sensor.
    void update(const QLowEnergyCharacteristic info, const QByteArray value);

private:
    QLowEnergyService* m_service;
    QBluetoothUuid m_characteristicUuid;
    QLowEnergyDescriptor m_descriptor;
    QLowEnergyCharacteristic::PropertyType m_property;
    QByteArray m_writeValue;

    void handleService();
    void handleCharacteristic();

};

#endif // BLESERVICEDECODER_H
