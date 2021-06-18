#include "DeviceInterface.h"
#include <QDebug>
#include <QtMath>

#define SENSOR_1_ADDRESS "D8:24:DA:C2:13:41"
#define SENSOR_2_ADDRESS "F4:A1:24:C1:1D:B9"

DeviceInterface::DeviceInterface(QObject *parent) : QObject(parent)
  , m_device(nullptr)
  , m_sensorAddress()
  , m_rpm(0)
  , m_mph(0)
  , m_wheelDiameterInches(21)
{
    // Update the speed reading when the sensor sets the rpm.
    connect(this, &DeviceInterface::rpmChanged, this, &DeviceInterface::updateMph);
}

DeviceInterface::~DeviceInterface()
{
    delete m_device;
    delete m_lowEnergyControl;
    delete m_cscDecoder;
    delete m_batteryDecoder;
}

QBluetoothDeviceInfo* DeviceInterface::device() const
{
    return m_device;
}

double DeviceInterface::rpm() const
{
    return m_rpm;
}

QString DeviceInterface::sensorAddress()
{
    return m_sensorAddress;
}

double DeviceInterface::wheelDiameterInches() const
{
    return m_wheelDiameterInches;
}

double DeviceInterface::mph() const
{
    return m_mph;
}

void DeviceInterface::setDevice(QBluetoothDeviceInfo* device)
{
    qDebug() << "Set device";
    if (!device)
    {
        qDebug() << "DeviceInterface::setDevice() - device is a nullptr.";
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
    m_sensorAddress = m_device->address().toString();

    // Connect to our bluetoothLE device.
    connectDevice(device);
}

void DeviceInterface::setWheelDiameterInches(double wheelDiameterInches)
{
    if (m_wheelDiameterInches == wheelDiameterInches)
        return;

    m_wheelDiameterInches = wheelDiameterInches;
    emit wheelDiameterInchesChanged(m_wheelDiameterInches);
}

void DeviceInterface::connectDevice(QBluetoothDeviceInfo* device)
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
        emit connected();
        dispatchServices();
    });
    connect(m_lowEnergyControl, &QLowEnergyController::disconnected, [=]() {
        qDebug() << "disconnected";
        emit disconnected();
    });
    connect(m_lowEnergyControl, &QLowEnergyController::stateChanged, [=](QLowEnergyController::ControllerState state) {
        qDebug() << "STATE:" << state;
    });
    connect(m_lowEnergyControl, static_cast<void (QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
            this, [=](QLowEnergyController::Error error) {
        qDebug() << error;
    });
}

void DeviceInterface::dispatchServices()
{
    // Discover this sensor's available services.
    m_lowEnergyControl->discoverServices();

    connect(m_lowEnergyControl, &QLowEnergyController::serviceDiscovered, this, [=](QBluetoothUuid uuid) {
        qDebug() << "Found Service:" << uuid.toString();
    });

    // Attach to the services that we want to use.
    connect(m_lowEnergyControl, &QLowEnergyController::discoveryFinished, this, [=]() {
        qDebug() << "Service Discovery Finished";
        for (QBluetoothUuid uuid : m_lowEnergyControl->services())
        {
            // Read Speed and Cadence service.
            if (uuid == QBluetoothUuid::CyclingSpeedAndCadence)
            {
                qDebug() << "CADENCE SERVICE FOUND";
                processCscService();
            }
            // Read Battery Service.
            if (uuid == QBluetoothUuid::BatteryService)
            {
                qDebug() << "BATTERY SERVICE FOUND";
                processBatteryService();
            }
        }
    });
}

void DeviceInterface::processCscService()
{
    // Initialize the service.
    QLowEnergyService* s = m_lowEnergyControl->createServiceObject(QBluetoothUuid::CyclingSpeedAndCadence);
    QBluetoothUuid uuid = QBluetoothUuid::CSCMeasurement;

    // Create decoder that will handle sending and recieving data from the sensor.
    m_cscDecoder = nullptr;
    delete m_cscDecoder;
    m_cscDecoder = new BleServiceDecoder(s);

    // Process the data sent by the sensor.
    connect(m_cscDecoder, &BleServiceDecoder::dataChanged, [=]() {
        // Cast to CscMeasurement to access the flags from this message.
        CscMeasurement_c* temp = (CscMeasurement_c*)m_cscDecoder->data().constData();
        updateRpmFromEvent(temp->flags);
    });

    // Start communications.
    m_cscDecoder->start(uuid, QLowEnergyCharacteristic::PropertyType::Notify);
}

void DeviceInterface::processBatteryService()
{
    // Initialize the service.
    QLowEnergyService* s = m_lowEnergyControl->createServiceObject(QBluetoothUuid::BatteryService);
    QBluetoothUuid uuid = QBluetoothUuid::BatteryLevel;

    // Create decoder to handle communication.
    m_batteryDecoder = nullptr;
    delete m_batteryDecoder;
    m_batteryDecoder = new BleServiceDecoder(s);

    // Process the data sent by the sensor.
    connect(m_batteryDecoder, &BleServiceDecoder::dataChanged, [=]() {
        // TODO: get data from the battery service.
    });

    // Start communications.
    m_batteryDecoder->start(uuid, QLowEnergyCharacteristic::PropertyType::Notify);
}

void DeviceInterface::updateRpmFromEvent(quint8 flags)
{
    quint16 prevRev;
    quint16 prevEvent;
    quint16 currentRev;
    quint16 currentEvent;

    if (flags & 0x2)
    {
        // Parse values from crank measurement.
        CscMeasurement_c* prev = (CscMeasurement_c*)m_cscDecoder->prevData().constData();
        CscMeasurement_c* current = (CscMeasurement_c*)m_cscDecoder->data().constData();
        prevRev = prev->revolutions;
        prevEvent = prev->lastEvent;
        currentRev = current->revolutions;
        currentEvent = current->lastEvent;
    }
    else
    {
        // Parse values from wheel measurement.
        CscMeasurement_w* prev = (CscMeasurement_w*)m_cscDecoder->prevData().constData();
        CscMeasurement_w* current = (CscMeasurement_w*)m_cscDecoder->data().constData();
        prevRev = prev->revolutions;
        prevEvent = prev->lastEvent;
        currentRev = current->revolutions;
        currentEvent = current->lastEvent;
    }

    int rotationsDelta = 0;
    int timeDelta = 0;

    // Calculate rotations delta.
    if (currentRev >= prevRev)
    {
        rotationsDelta = currentRev - prevRev;
    }
    else
    {
        // Data overflow, calculate the difference.
        int temp = 0xFFFF - prevRev;
        rotationsDelta = temp + currentRev;
    }

    // Calculate event time delta.
    if (currentEvent >= prevEvent)
    {
        timeDelta = currentEvent - prevEvent;
    }
    else
    {
        // Data overflow, calculate the difference.
        int temp = 0xFFFF - prevEvent;
        timeDelta = temp + currentEvent;
    }

    // Covert time delta to minutes.
    double timeDelta_minutes = (double)(timeDelta) / 1024.0 / 60.0;

    // Calculate RPM.
    double potentialRpm = rotationsDelta/timeDelta_minutes;

    // Set an upper and lower limit to the rpm data.
    if (potentialRpm < 650 && potentialRpm > 0)
    {
        m_rpm = potentialRpm;
    }
    // If the potential rpm value was out of bounds, we'll still use the last value.
    emit rpmChanged(m_rpm);
}

void DeviceInterface::updateMph(double rpm)
{
    double inchPerMinute = rpm * (M_PI * m_wheelDiameterInches);
    m_mph = inchPerMinute / 12 / 5280 * 60; // Convert in/min to m/hr.
    emit mphChanged(m_mph);
}
