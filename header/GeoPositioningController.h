#ifndef GEOPOSITIONINGCONTROLLER_H
#define GEOPOSITIONINGCONTROLLER_H

#include "./header/DbController.h"
#include "./header/DeviceInterface.h"

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

    Q_PROPERTY(Trip* currentTrip READ currentTrip WRITE setCurrentTrip NOTIFY currentTripChanged)
    Q_PROPERTY(QList<Trip*> trips READ trips NOTIFY tripsChanged)
    Q_PROPERTY(TripState tripState READ tripState WRITE setTripState NOTIFY tripStateChanged)

    enum class TripState {
        Inactive,
        Active
    }; Q_ENUM(TripState)

    // Start/Stop the satellite updates.
    Q_INVOKABLE void start(Trip* trip=nullptr);
    Q_INVOKABLE void stop();

    // Create a new Trip.
    Q_INVOKABLE void createTrip(QString name="New Trip", QDateTime startTime=QDateTime::currentDateTime(), QDateTime endTime=QDateTime::currentDateTime());
    Q_INVOKABLE void deleteTrip(Trip* trip);

    Q_INVOKABLE void deleteAllTripData();

    // Log geo position to the database.
    void logPosition(QGeoPositionInfo geo);

    Trip* currentTrip() const;
    QList<Trip*> trips() const;
    TripState tripState() const;

public slots:
    void setCurrentTrip(Trip* currentTrip);
    void setTrips(QList<Trip*> trips);    
    void setTripState(TripState tripState);

signals:
    void currentTripChanged(Trip* currentTrip);
    void tripsChanged(QList<Trip*> trips);    
    void tripStateChanged(TripState tripState);

private:
    DbController* m_database;
    DeviceInterface* m_cadence;
    QGeoPositionInfoSource* m_positioningSource;

    Trip* m_currentTrip;
    QList<Trip*> m_trips;
    TripState m_tripState;
};

#endif // GEOPOSITIONINGCONTROLLER_H
