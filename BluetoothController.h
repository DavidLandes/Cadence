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

#include "DeviceInterface.h"
#include "Device.h"

class BluetoothController : public QObject
{
    Q_OBJECT
public:
    explicit BluetoothController(DeviceInterface* sensor1, QSettings* settings, QObject *parent = nullptr);
    ~BluetoothController();

    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QList<Device*> discoveredDevices READ discoveredDevices NOTIFY discoveredDevicesChanged)

    // TODO: refactor states. DeviceInterface state (connected, disconnected), Controller state should be more basic (idle, scanning) only
    enum class State {
        Idle,
        Scanning,
        Paired
    }; Q_ENUM(State)

    void initialize();
    Q_INVOKABLE void startDeviceDiscovery();
    Q_INVOKABLE void stopDeviceDiscovery();
    Q_INVOKABLE void clearDiscoveredDevices();

    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    State state() const;
    QList<Device*> discoveredDevices() const;

public slots:
    void setState(State state);

signals:
    void stateChanged(State state);
    void discoveredDevicesChanged(QList<Device*> discoveredDevices);

private:
    QBluetoothDeviceDiscoveryAgent* m_discoveryAgent;
    QList<Device*> m_discoveredDevices;
    QBluetoothLocalDevice* m_localDevice;
    State m_state;

    QSettings* m_settings;

    DeviceInterface* m_cadence1;
};

#endif // BLUETOOTHCONTROLLER_H
