#include "BleServiceDecoder.h"
#include <QtEndian>

BleServiceDecoder::BleServiceDecoder(QLowEnergyService* service, QBluetoothUuid characteristicUuid, QLowEnergyCharacteristic::PropertyType property, QByteArray writeValue, QObject *parent) : QObject(parent)
{
    m_service = service;
    m_characteristicUuid = characteristicUuid;
    m_property = property;

    // Store the value we want to write to the sensor. Otherwise, writeValue will not be used.
    m_writeValue = writeValue;

}

void BleServiceDecoder::start()
{
    handleService();
}

void BleServiceDecoder::handleService()
{
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
                connect(m_service, &QLowEnergyService::characteristicRead, this, [=](QLowEnergyCharacteristic c, QByteArray data) {
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

        if (info.uuid() == QBluetoothUuid::CSCMeasurement)
        {
            qDebug() << "HEX DATA:" << value.toHex('-') << value.count()*8;

            const char* data = value.constData();

            const CscMeasurement* payload = reinterpret_cast<const CscMeasurement*>(data);

    //        QString wheelRev = QString::number(qFromLittleEndian<quint8>(payload->wheelRevolutions), 16);
    //        QString eventTime = QString::number(qFromLittleEndian<quint16>(payload->lastWheelEvent), 16);
    //        QString crankRev = QString::number(qFromLittleEndian<quint8>(payload->crankRevolutions), 16);

    //        quint8 wheelRev = qFromLittleEndian<quint8>(payload->wheelRevolutions);
    //        quint16 eventTime = qFromLittleEndian<quint16>(payload->lastWheelEvent);
    //        quint8 crankRev = qFromLittleEndian<quint8>(payload->crankRevolutions);

    //        qDebug() << payload->flags << wheelRev << eventTime << crankRev;

            //qDebug() << value.toHex()[0] << value.toHex()[1] << value.toHex()[2] << ((value.toHex()[3] << 8) | value.toHex()[4]);
            qDebug() << QString::number(payload->crankRevolutions, 16) << QString::number(payload->wheelRevolutions, 16) << QString::number(payload->lastWheelEvent, 16);
        }



        qDebug() << "Characteristic Changed!!!!";
    });


}
