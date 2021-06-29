#ifndef TRIPDAO_H
#define TRIPDAO_H

#include "Trip.h"

#include <QObject>
#include <QSqlQuery>

class TripDao : public QObject
{
    Q_OBJECT
public:
    explicit TripDao(QObject *parent = nullptr);

    void saveTrip(QString name, QDateTime startTime, QDateTime endTime);
    Trip* getTrip(int tripId);
    Trip* toEntity(QSqlQuery query);

signals:

};

#endif // TRIPDAO_H
