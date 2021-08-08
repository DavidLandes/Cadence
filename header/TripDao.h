#ifndef TRIPDAO_H
#define TRIPDAO_H

#include "./header/Trip.h"

#include <QObject>
#include <QSqlQuery>

class TripDao : public QObject
{
    Q_OBJECT
public:
    explicit TripDao(QObject *parent = nullptr);

    // Returns the saved item.
    Trip* saveTrip(QString name, int pathId, QDateTime startTime, QDateTime endTime);
    Trip* getTrip(int tripId);
    QList<Trip*> getAll();
    void deleteTrip(int tripId);
    void deleteAll();
    Trip* toEntity(QSqlQuery query);

signals:

private:
    Trip* lastRecord();

};

#endif // TRIPDAO_H
