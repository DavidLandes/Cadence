#ifndef BLEMESSAGE_H
#define BLEMESSAGE_H

#include <QObject>
#include <QtEndian>

struct CscMeasurement {
    quint8 flags                :8;
    quint8 crankRevolutions     :8;
    quint8 wheelRevolutions     :8;
    quint16 lastWheelEvent      :16;


//    enum class Flags {
//        Wheel_Rev_Present = 0,
//        Crank_Rev_Present,
//        Multiple_Sensor_Locations,
//        Unused
//    };
};

class BleMessage
{
public:
    BleMessage(const QByteArray payload, int messageType);

    enum class Type {
        CscMeasurement
    };

//    struct CscMeasurement {
//        quint8 flags                :8;
//        quint32 wheelRevolutions    :32;
//        quint16 lastWheelEvent      :16;
//        quint16 crankRevolutions    :16;
//        quint16 lastCrankEvent      :16;


//        enum class Flags {
//            Wheel_Rev_Present = 0,
//            Crank_Rev_Present,
//            Multiple_Sensor_Locations,
//            Unused
//        };
//    };

private:
    void processPayload();

};

#endif // BLEMESSAGE_H
