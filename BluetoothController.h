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

class BluetoothController : public QObject
{
    Q_OBJECT
public:
    explicit BluetoothController(DeviceInterface* sensor1, QSettings* settings, QObject *parent = nullptr);
    ~BluetoothController();

    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QStringList discoveredDeviceNames READ discoveredDeviceNames NOTIFY discoveredDeviceNamesChanged)
    Q_PROPERTY(QList<QBluetoothDeviceInfo*> discoveredDevices READ discoveredDevices NOTIFY discoveredDevicesChanged)

    // TODO: refactor states. DeviceInterface state (connected, disconnected), Controller state should be more basic (idle, scanning) only
    enum class State {
        Idle,
        Scanning,
        Paired
    }; Q_ENUM(State)

    void initialize();
    Q_INVOKABLE void startDeviceDiscovery();
    Q_INVOKABLE void stopDeviceDiscovery();
    Q_INVOKABLE void setCadenceDevice(QString name);

    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    State state() const;
    QList<QBluetoothDeviceInfo*> discoveredDevices() const;
    QStringList discoveredDeviceNames() const;

public slots:
    void setState(State state);

signals:
    void stateChanged(State state);
    void discoveredDevicesChanged(QList<QBluetoothDeviceInfo*> discoveredDevices);
    void discoveredDeviceNamesChanged(QStringList discoveredDeviceNames);

private:
    QBluetoothDeviceDiscoveryAgent* m_discoveryAgent;
    QList<QBluetoothDeviceInfo*> m_discoveredDevices;
    QStringList m_discoveredDeviceNames;
    QBluetoothLocalDevice* m_localDevice;
    State m_state;

    QSettings* m_settings;

    DeviceInterface* m_cadence1;
};

#endif // BLUETOOTHCONTROLLER_H
