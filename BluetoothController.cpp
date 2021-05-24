#include "BluetoothController.h"

#define CONNECTION_TIMEOUT_MSEC 30*1000
#define SENSOR_1_ADDRESS "D8:24:DA:C2:13:41"
#define SENSOR_2_ADDRESS "F4:A1:24:C1:1D:B9"

BluetoothController::BluetoothController(BluetoothInterface* sensor1, QSettings* settings, QObject *parent) : QObject(parent)
  , m_settings(settings)
{
    // Setup sensor interface.
    m_cadence1 = sensor1;

    // Setup bluetooth device discovery.
    m_localDevice = new QBluetoothLocalDevice();
    m_discoveryAgent = new QBluetoothDeviceDiscoveryAgent();

    initialize();
   // startDeviceDiscovery();

    // Discover devices.
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BluetoothController::deviceDiscovered);
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, [=]() {
        //setState(State::Idle);
    });
}

BluetoothController::~BluetoothController()
{
    delete m_localDevice;
    delete m_discoveryAgent;
}

void BluetoothController::initialize()
{
    // Initialize bluetooth.
    m_localDevice->setHostMode(QBluetoothLocalDevice::HostConnectable);
   // m_cadence1->setState(Bluetooth::State::Idle);

    // Remember the initial bluetooth status of the local device.
    bool isBlOff = m_localDevice->hostMode() == QBluetoothLocalDevice::HostMode::HostPoweredOff;
    m_settings->setValue("Bluetooth/BlOnAtStartup", !isBlOff);
}

void BluetoothController::startDeviceDiscovery()
{
    // Setup the connection timeout.
    m_discoveryAgent->setLowEnergyDiscoveryTimeout(CONNECTION_TIMEOUT_MSEC);

    // Start a discovery
    if (m_discoveryAgent->isActive())
        m_discoveryAgent->stop();
    m_discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BluetoothController::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';

    if (device.address().toString() != "")
    {
        qDebug() << "valid address" ;
        if (device.address().toString() == SENSOR_2_ADDRESS)
        {
            qDebug() << "Sensor match!";
            // The memory allocated here is managed by the BluetoothInterface m_cadence1.
            QBluetoothDeviceInfo* d = new QBluetoothDeviceInfo(device);
            m_cadence1->setDevice(d);
        }
    }
}
