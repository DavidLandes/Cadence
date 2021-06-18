#ifndef BLESERVICEDECODER_H
#define BLESERVICEDECODER_H

#pragma once
#include <QObject>
#include <QBluetoothLocalDevice>
#include <QBluetoothAddress>
#include <QBluetoothUuid>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QTimer>

#include "BluetoothFrames.h"

class BleServiceDecoder : public QObject
{
    Q_OBJECT
public:
    explicit BleServiceDecoder(QLowEnergyService* service, QObject *parent = nullptr);

    Q_PROPERTY(QByteArray data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(QByteArray prevData READ prevData WRITE setPrevData NOTIFY prevDataChanged)

    // Start communication.
    // characteristicUuid - ID of the sensor characteristic.
    // property - The property type of this characteristic. This describes the relationship of our communication with the sensor.
    // writeValue - Only necessary if data needs to be sent to the sensor. This is indicated by the property value.
    void start(QBluetoothUuid characteristicUuid, QLowEnergyCharacteristic::PropertyType property, QByteArray writeValue=QByteArray::fromHex("0000"));

    QByteArray data() const;
    QByteArray prevData() const;

public slots:
    void setData(QByteArray data);
    void setPrevData(QByteArray prevData);

signals:
    void dataChanged(QByteArray data);
    void prevDataChanged(QByteArray prevData);

private:
    QLowEnergyService* m_service;
    QBluetoothUuid m_characteristicUuid;
    QLowEnergyDescriptor m_descriptor;
    QLowEnergyCharacteristic::PropertyType m_property;
    QByteArray m_writeValue;

    void handleService();
    void handleCharacteristic();

    QByteArray m_data;
    QByteArray m_prevData;
};

#endif // BLESERVICEDECODER_H
