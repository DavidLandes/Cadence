#ifndef DEVICE_H
#define DEVICE_H

#include <QBluetoothDeviceInfo>
#include <QBluetoothAddress>
#include <QObject>

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QBluetoothDeviceInfo* device, QObject *parent = nullptr);
    ~Device();

    QBluetoothDeviceInfo* info();
    Q_INVOKABLE QString name();
    Q_INVOKABLE QString address();

signals:

private:
    QBluetoothDeviceInfo* m_info;

};

#endif // DEVICE_H
