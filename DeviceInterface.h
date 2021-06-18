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
#include "BluetoothFrames.h"

class DeviceInterface : public QObject
{
    Q_OBJECT
public:
    explicit DeviceInterface(QObject *parent = nullptr);
    ~DeviceInterface();

    Q_PROPERTY(QBluetoothDeviceInfo* device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(double wheelDiameterInches READ wheelDiameterInches WRITE setWheelDiameterInches NOTIFY wheelDiameterInchesChanged)
    Q_PROPERTY(double rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(double mph READ mph NOTIFY mphChanged)

    // Getters.
    QBluetoothDeviceInfo* device() const;
    double rpm() const;
    double mph() const;

    // Functions.
    QString sensorAddress();
    double wheelDiameterInches() const;

public slots:
    void setDevice(QBluetoothDeviceInfo* device);
    void setWheelDiameterInches(double wheelDiameterInches);

signals:
    void deviceChanged(QBluetoothDeviceInfo* device);
    void connected();
    void disconnected();
    void rpmChanged(double rpm);
    void mphChanged(double mph);
    void wheelDiameterInchesChanged(double wheelDiameterInches);

private:
    QLowEnergyController* m_lowEnergyControl;
    BleServiceDecoder* m_cscDecoder;
    BleServiceDecoder* m_batteryDecoder;
    QBluetoothDeviceInfo* m_device;

    // The address registered for this DeviceInterface. This is the address used to find and pair with the correct device.
    QString m_sensorAddress;

    void connectDevice(QBluetoothDeviceInfo* device);

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
