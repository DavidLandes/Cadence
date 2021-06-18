#include "BluetoothController.h"

#define CONNECTION_TIMEOUT_MSEC 30*1000

BluetoothController::BluetoothController(DeviceInterface* sensor1, QSettings* settings, QObject *parent) : QObject(parent)
  , m_settings(settings)
  , m_state(State::Idle)
{
    // Setup sensor interface.
    m_cadence1 = sensor1;

    // Setup bluetooth device discovery.
    m_localDevice = new QBluetoothLocalDevice();
    m_discoveryAgent = new QBluetoothDeviceDiscoveryAgent();

    initialize();
    startDeviceDiscovery();

    // Discover devices.
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BluetoothController::deviceDiscovered);
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::canceled, this, [=]() {
        setState(State::Idle);
    });
    connect(m_discoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error), [=](QBluetoothDeviceDiscoveryAgent::Error error) {
        setState(State::Idle);
    });
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, [=]() {
        if (m_state != State::Paired)
        {
            setState(State::Idle);
        }
    });

    // Set state
    connect(m_cadence1, &DeviceInterface::connected, [=]() { setState(State::Paired); });
    connect(m_cadence1, &DeviceInterface::disconnected, [=]() { setState(State::Idle); });
}

BluetoothController::~BluetoothController()
{
    delete m_localDevice;
    delete m_discoveryAgent;
    for (QBluetoothDeviceInfo* dev : m_discoveredDevices)
    {
        delete dev;
    }
}

void BluetoothController::initialize()
{
    // Initialize bluetooth.
    m_localDevice->setHostMode(QBluetoothLocalDevice::HostConnectable);

    // Remember the initial bluetooth status of the local device.
    bool isBlOff = m_localDevice->hostMode() == QBluetoothLocalDevice::HostMode::HostPoweredOff;
    m_settings->setValue("Bluetooth/BlOnAtStartup", !isBlOff);
}

void BluetoothController::startDeviceDiscovery()
{
    m_discoveredDevices.clear(); // TODO: Possible memory leak, but if we delete all devices, the DeviceInterface could still be using the pointer.
    emit discoveredDevicesChanged(m_discoveredDevices);

    m_discoveredDeviceNames.clear();
    emit discoveredDeviceNamesChanged(m_discoveredDeviceNames);

    // Setup the connection timeout.
    m_discoveryAgent->setLowEnergyDiscoveryTimeout(CONNECTION_TIMEOUT_MSEC);

    // Start a discovery
    if (m_discoveryAgent->isActive())
    {
        stopDeviceDiscovery();
    }
    m_discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    setState(State::Scanning);
}

void BluetoothController::stopDeviceDiscovery()
{
    m_discoveryAgent->stop();
    setState(State::Idle);
}

void BluetoothController::setCadenceDevice(QString device)  // TODO: what about duplicate names? we need to compare addresses, but displaying an address isn't user friendly..
{
    for(QBluetoothDeviceInfo* dev : m_discoveredDevices)
    {
        // Connect to our sensor.
        if (dev->name() == device)
        {
            //   qDebug() << "Sensor match!";
            m_cadence1->setDevice(dev);
            qDebug() << "Device found";
            return;
        }
    }
    qDebug() << "No device with this name was found..";
}

void BluetoothController::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';

    if (device.address().toString() != "")
    {
        // If data is valid, add to list of discovered devices.
        if (device.name() != "")
        {
            QBluetoothDeviceInfo* d = new QBluetoothDeviceInfo(device);

            m_discoveredDevices.append(d);
            emit discoveredDevicesChanged(m_discoveredDevices);

            m_discoveredDeviceNames.append(d->name());
            emit discoveredDeviceNamesChanged(m_discoveredDeviceNames);

            qDebug() << "device added";
        }
    }
}

BluetoothController::State BluetoothController::state() const
{
    return m_state;
}

QStringList BluetoothController::discoveredDeviceNames() const
{
    return m_discoveredDeviceNames;
}

QList<QBluetoothDeviceInfo*> BluetoothController::discoveredDevices() const
{
    return m_discoveredDevices;
}

void BluetoothController::setState(BluetoothController::State state)
{
    if (m_state == state)
        return;

    m_state = state;
    emit stateChanged(m_state);
}
