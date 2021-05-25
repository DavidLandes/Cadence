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
    explicit BleServiceDecoder(QLowEnergyService* service, QObject *parent = nullptr);

    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)
    enum class State {
        Idle,
        Busy
    };

    // Start communication.
    // characteristicUuid - ID of the sensor characteristic.
    // property - The property type of this characteristic. This describes the relationship of our communication with the sensor.
    // writeValue - Only necessary if data needs to be sent to the sensor. This is indicated by the property value.
    void start(QBluetoothUuid characteristicUuid, QLowEnergyCharacteristic::PropertyType property, QByteArray writeValue=QByteArray::fromHex("0000"));

    // data - pointer to the payload data. To handle this data, reinterpret_cast this to the appropriate BleMessage to access sections of bits.
    char* data;
    State state() const;

public slots:
    void setState(State state);

signals:
    // Signal emitted when characteristic data is recieved from the sensor.
    void finished();
    void stateChanged(State state);

private:
    QLowEnergyService* m_service;
    QBluetoothUuid m_characteristicUuid;
    QLowEnergyDescriptor m_descriptor;
    QLowEnergyCharacteristic::PropertyType m_property;
    QByteArray m_writeValue;

    void handleService();
    void handleCharacteristic();

    State m_state;
};

#endif // BLESERVICEDECODER_H
