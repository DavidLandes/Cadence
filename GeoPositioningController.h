#ifndef GEOPOSITIONINGCONTROLLER_H
#define GEOPOSITIONINGCONTROLLER_H

#include "DbController.h"
#include "DeviceInterface.h"

#include <QObject>
#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>
#include <QGeoCoordinate>
#include <QTimer>

class GeoPositioningController : public QObject
{
    Q_OBJECT
public:
    explicit GeoPositioningController(DbController* dbControl, DeviceInterface* cadence, QObject *parent = nullptr);
    ~GeoPositioningController();

    Q_PROPERTY(Trip* currentTrip READ currentTrip NOTIFY currentTripChanged)
    Q_PROPERTY(QList<Trip*> trips READ trips NOTIFY tripsChanged)

    // Start/Stop the satellite updates.
    Q_INVOKABLE void start(Trip* trip);
    Q_INVOKABLE void stop();

    // Create a new Trip.
    Q_INVOKABLE void createTrip(QString name="New Trip", QDateTime startTime=QDateTime::currentDateTime(), QDateTime endTime=QDateTime::currentDateTime());
    Q_INVOKABLE void deleteTrip(Trip* trip);

    // Log geo position to the database.
    void logPosition(QGeoPositionInfo geo);

    Trip* currentTrip() const;
    QList<Trip*> trips() const;

public slots:
    void setCurrentTrip(Trip* currentTrip);
    void setTrips(QList<Trip*> trips);

signals:
    void currentTripChanged(Trip* currentTrip);
    void tripsChanged(QList<Trip*> trips);

private:
    DbController* m_database;
    DeviceInterface* m_cadence;
    QGeoPositionInfoSource* m_positioningSource;

    Trip* m_currentTrip;
    QList<Trip*> m_trips;
};

#endif // GEOPOSITIONINGCONTROLLER_H
