#include "BleMessage.h"


BleMessage::BleMessage(const QByteArray payload, int messageType)
{
    switch (messageType) {

    case (int)Type::CscMeasurement:
        const char* constData = payload.constData();
        const auto data = reinterpret_cast<const CscMeasurement*>(constData);

       // qDebug() << payload->flags << payload->wheelRevolutions << payload->lastWheelEvent << payload->crankRevolutions << payload->lastCrankEvent;

//        QString wheelRev = QString::number(qFromLittleEndian<quint32>(payload->wheelRevolutions), 16);
//        QString wheelTime = QString::number(qFromLittleEndian<quint16>(payload->lastWheelEvent), 16);
//        QString crankRev = QString::number(qFromLittleEndian<quint16>(payload->crankRevolutions), 16);
//        QString crankTime = QString::number(qFromLittleEndian<quint16>(payload->lastCrankEvent), 16);
        break;
    }
}
