#include "BluetoothInterface.h"
#include <QDebug>


BluetoothInterface::BluetoothInterface(QObject *parent) : QObject(parent)
  , m_device(nullptr)
{

}

BluetoothInterface::~BluetoothInterface()
{
    delete m_device;
    delete m_lowEnergyControl;
    delete m_cscDecoder;
}

QBluetoothDeviceInfo* BluetoothInterface::device() const
{
    return m_device;
}

void BluetoothInterface::setDevice(QBluetoothDeviceInfo* device)
{
    qDebug() << "Set device";
    if (!device)
    {
        qDebug() << "BluetoothInterface::setDevice() - device is a nullptr.";
        return;
    }

    if (m_device == device)
        return;

    // Deallocate the old device before setting a new device.
    if (m_device)
    {
        m_device = nullptr;
        delete m_device;
    }

    m_device = device;
    emit deviceChanged(m_device);

    // Connect to our bluetoothLE device.
    connectDevice(device);
}

void BluetoothInterface::connectDevice(QBluetoothDeviceInfo* device)
{
    // Initiate connection.
    if (m_lowEnergyControl)
    {
        m_lowEnergyControl = nullptr;
        delete m_lowEnergyControl;
    }
    m_lowEnergyControl = new QLowEnergyController(device->address());
    m_lowEnergyControl->connectToDevice();

    // Connect to controller signals.
    connect(m_lowEnergyControl, &QLowEnergyController::connected, [=]() {
        qDebug() << "connected";
        handleServices();
    });
    connect(m_lowEnergyControl, &QLowEnergyController::disconnected, [=]() {
        qDebug() << "disconnected";
    });
    connect(m_lowEnergyControl, &QLowEnergyController::stateChanged, [=](QLowEnergyController::ControllerState state) {
        qDebug() << "STATE:" << state;
    });
    connect(m_lowEnergyControl, static_cast<void (QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
            this, [=](QLowEnergyController::Error error) {
        qDebug() << error;
    });
}

void BluetoothInterface::handleServices()
{
    m_lowEnergyControl->discoverServices();

    connect(m_lowEnergyControl, &QLowEnergyController::serviceDiscovered, this, [=](QBluetoothUuid uuid) {
        qDebug() << "Found Service:" << uuid.toString();
    });

    connect(m_lowEnergyControl, &QLowEnergyController::discoveryFinished, this, [=]() {
        qDebug() << "Service Discovery Finished";
        for (QBluetoothUuid uuid : m_lowEnergyControl->services())
        {
            // Read Speed and Cadence service.
            if (uuid == QBluetoothUuid::CyclingSpeedAndCadence)
            {
                qDebug() << "CADENCE SERVICE FOUND";
                // Initialize the service.
                QLowEnergyService* s = m_lowEnergyControl->createServiceObject(QBluetoothUuid::CyclingSpeedAndCadence);
                QBluetoothUuid uuid = QBluetoothUuid::CSCMeasurement;

                // Create decoder that will handle sending and recieving data from the sensor.
                m_cscDecoder = new BleServiceDecoder(s, uuid, QLowEnergyCharacteristic::PropertyType::Notify);
                m_cscDecoder->start();
            }
            // Read Battery Service.
            if (uuid == QBluetoothUuid::BatteryService)
            {
                qDebug() << "BATTERY SERVICE FOUND";
            }
        }
    });
}
