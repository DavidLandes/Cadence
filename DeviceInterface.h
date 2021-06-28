#ifndef BLUETOOTH_H
#define BLUETOOTH_H

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
#include <QSettings>

#include "BleServiceDecoder.h"
#include "BluetoothController.h"
#include "BluetoothFrames.h"
#include "Device.h"

class DeviceInterface : public QObject
{
    Q_OBJECT
public:
    explicit DeviceInterface(BluetoothController* blController, QSettings* settings, QObject *parent = nullptr);
    ~DeviceInterface();

    Q_PROPERTY(Device* device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(double wheelDiameterInches READ wheelDiameterInches WRITE setWheelDiameterInches NOTIFY wheelDiameterInchesChanged)
    Q_PROPERTY(double rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(double mph READ mph NOTIFY mphChanged)

    Device* device() const;
    double rpm() const;
    double mph() const;
    double wheelDiameterInches() const;

public slots:
    void setDevice(Device* device);
    void setWheelDiameterInches(double wheelDiameterInches);

signals:
    void deviceChanged(Device* device);
    void connected();
    void disconnected();
    void rpmChanged(double rpm);
    void mphChanged(double mph);
    void wheelDiameterInchesChanged(double wheelDiameterInches);

private:
    QSettings* m_settings;

    BluetoothController* m_blControl;
    QLowEnergyController* m_lowEnergyControl;
    BleServiceDecoder* m_cscDecoder;
    BleServiceDecoder* m_batteryDecoder;
    Device* m_device;

    void connectDevice(QBluetoothDeviceInfo* device);
    void disconnectDevice();

    void dispatchServices();
    void processCscService();
    void processBatteryService();

    void updateRpmFromEvent(quint8);
    void updateMph(double rpm);

    double m_rpm;
    double m_mph;
    double m_wheelDiameterInches;
};

#endif // BLUETOOTH_H
