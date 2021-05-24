#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>
#include <QBluetoothLocalDevice>
#include <QBluetoothAddress>
#include <QBluetoothUuid>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QTimer>

#include "BleServiceDecoder.h"

class BluetoothInterface : public QObject
{
    Q_OBJECT
public:
    explicit BluetoothInterface(QObject *parent = nullptr);
    ~BluetoothInterface();

    Q_PROPERTY(QBluetoothDeviceInfo* device READ device WRITE setDevice NOTIFY deviceChanged)

    QBluetoothDeviceInfo* device() const;

public slots:
    void setDevice(QBluetoothDeviceInfo* device);

signals:
    void deviceChanged(QBluetoothDeviceInfo* device);

private:
    QLowEnergyController* m_lowEnergyControl;

    BleServiceDecoder* m_cscDecoder;

    QBluetoothDeviceInfo* m_device;

    void connectDevice(QBluetoothDeviceInfo* device);
    void handleServices();
};

#endif // BLUETOOTH_H
