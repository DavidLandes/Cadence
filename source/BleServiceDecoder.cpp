#include "./header/BleServiceDecoder.h"
#include <QDataStream>
#include <QtEndian>

BleServiceDecoder::BleServiceDecoder(QLowEnergyService* service, QObject *parent) : QObject(parent)
  , m_data(0)
  , m_prevData(0)
{
    m_service = service;

}

void BleServiceDecoder::start(QBluetoothUuid characteristicUuid, QLowEnergyCharacteristic::PropertyType property, QByteArray writeValue)
{

    m_characteristicUuid = characteristicUuid;
    m_property = property;

    // Store the value we want to write to the sensor. Otherwise, writeValue will not be used.
    m_writeValue = writeValue;

    handleService();
}

QByteArray BleServiceDecoder::data() const
{
    return m_data;
}

QByteArray BleServiceDecoder::prevData() const
{
    return m_prevData;
}

void BleServiceDecoder::setData(QByteArray data)
{
    if (m_data == data)
        return;

    m_data = data;
    emit dataChanged(m_data);
}

void BleServiceDecoder::setPrevData(QByteArray prevData)
{
    if (m_prevData == prevData)
        return;

    m_prevData = prevData;
    emit prevDataChanged(m_prevData);
}

void BleServiceDecoder::handleService()
{
    // Disconnect all the old signals.
    disconnect(m_service, nullptr);

    // Order matters here. Connect signals, then discover details.
    handleCharacteristic();
    m_service->discoverDetails();
}

void BleServiceDecoder::handleCharacteristic()
{
    // Handle service's signals.
    connect(m_service, &QLowEnergyService::stateChanged, this, [=](QLowEnergyService::ServiceState state) {
        switch (state)
        {
        case QLowEnergyService::InvalidService:
            qDebug() << "Error: Invalid Service";
            break;

        case QLowEnergyService::DiscoveringServices:
            break;

        case QLowEnergyService::ServiceDiscovered:
        {
            qDebug() << "Characteristic Discovered!!!!";
            // Validate the characteristic.
            const QLowEnergyCharacteristic characteristic = m_service->characteristic(QBluetoothUuid(m_characteristicUuid));
            if (!characteristic.isValid()) {
                qDebug() << "Characteristic not found";
                break;
            }

            // Decode the characteristic.
            int prop = (int)m_property;
            switch (prop) {

            case ((int)QLowEnergyCharacteristic::PropertyType::Read):
                // Read characteristic from sensor.
                m_service->readCharacteristic(characteristic);
                connect(m_service, &QLowEnergyService::characteristicRead, this, [=](QLowEnergyCharacteristic c, QByteArray data) {
                    qDebug() << "Characteristic READ" << c.name() << data;
                });
                break;

            case ((int)QLowEnergyCharacteristic::PropertyType::Write):
                // Write characteristic on the sensor.
                m_service->writeCharacteristic(characteristic, m_writeValue);
                connect(m_service, &QLowEnergyService::characteristicWritten, this, [=](QLowEnergyCharacteristic c, QByteArray data) {
                    qDebug() << "Characteristic WRITE" << c.name() << data;
                });
                break;

            case ((int)QLowEnergyCharacteristic::PropertyType::Notify):
                // Tell the sensor we want to subscribe to this characteristic.
                m_descriptor = characteristic.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
                if (m_descriptor.isValid())
                {
                    qDebug() << "write descriptor";
                    m_service->writeDescriptor(m_descriptor, QByteArray::fromHex("0100"));  // QBluetoothUuid::L2cap = 0x0100 (Communication Protocol)
                }
                else
                {
                    qDebug() << "Invalid descriptor";
                }
                break;

            case ((int)QLowEnergyCharacteristic::PropertyType::Indicate):
                // Nothing for now. May not need this, but could be useful in the future.
                break;

            default:
                // Nothing for now
                break;
            }
        }

        default:
            // Nothing for now
            break;
        }
    });

    // Notify that sensor data has been recieved.
    connect(m_service, &QLowEnergyService::characteristicChanged, this, [=](const QLowEnergyCharacteristic info, const QByteArray value) {        
        setPrevData(m_data);
        setData(value);
    });
}
