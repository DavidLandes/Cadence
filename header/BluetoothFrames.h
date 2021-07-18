#ifndef BLUETOOTHFRAMES_H
#define BLUETOOTHFRAMES_H

#pragma pack(1)

#include <QObject>
#include <QtEndian>


struct CscMeasurement_w {
    quint8 flags            :8;
    quint16 revolutions     :16;
    quint16 unused          :16;
    quint16 lastEvent       :16;
};

struct CscMeasurement_c {
    quint8 flags            :8;
    quint16 revolutions     :16;
    quint16 lastEvent       :16;
};



#endif // BLUETOOTHFRAMES_H
