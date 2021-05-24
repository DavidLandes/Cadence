#ifndef BLUETOOTHCONTROLLER_H
#define BLUETOOTHCONTROLLER_H

#include <QObject>
#include <QSettings>
#include <QBluetoothLocalDevice>
#include <QBluetoothAddress>
#include <QBluetoothUuid>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QTimer>

#include "BluetoothInterface.h"

class BluetoothController : public QObject
{
    Q_OBJECT
public:
    explicit BluetoothController(BluetoothInterface* sensor1, QSettings* settings, QObject *parent = nullptr);
    ~BluetoothController();

    void initialize();
    Q_INVOKABLE void startDeviceDiscovery();

    void deviceDiscovered(const QBluetoothDeviceInfo &device);

signals:

private:
    QBluetoothDeviceDiscoveryAgent* m_discoveryAgent;
    QBluetoothLocalDevice* m_localDevice;

    QSettings* m_settings;

    BluetoothInterface* m_cadence1;

};

#endif // BLUETOOTHCONTROLLER_H
