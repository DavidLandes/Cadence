#ifndef TRAVELCONTROLLER_H
#define TRAVELCONTROLLER_H

#include "./header/DbController.h"
#include "./header/GeoPositioningController.h"
#include "./header/Path.h"
#include "./header/Trip.h"
#include "./header/Position.h"

#include <QObject>

// This is where trips & paths can be created, managed, or deleted.
class TravelController : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(Path* currentPath READ currentPath WRITE setCurrentPath NOTIFY currentPathChanged)
    Q_PROPERTY(QList<Path*> paths READ paths WRITE setPaths NOTIFY pathsChanged)

    Q_PROPERTY(Trip* currentTrip READ currentTrip WRITE setCurrentTrip NOTIFY currentTripChanged)
    Q_PROPERTY(QList<Trip*> trips READ trips NOTIFY tripsChanged)
    Q_PROPERTY(TripState tripState READ tripState WRITE setTripState NOTIFY tripStateChanged)

    enum class TripState {
        Inactive,
        Active
    }; Q_ENUM(TripState)

    explicit TravelController(DbController* database, GeoPositioningController* geoController, QObject *parent = nullptr);
    // TODO: move current trip to this class from geoPositioningcontroller. geocontroller should get geoposition and send that coordinate here to be stored.

    Q_INVOKABLE void createPath(QString name);
    Q_INVOKABLE void deletePath(Path* path);

    Q_INVOKABLE void createTrip(QString name="New Trip", QDateTime startTime=QDateTime::currentDateTime(), QDateTime endTime=QDateTime::currentDateTime());
    Q_INVOKABLE void deleteTrip(Trip* trip);

    void logPosition(QGeoPositionInfo geo, double velocityMph);

    QList<Path*> paths() const;
    Path* currentPath() const;

    Trip* currentTrip() const;
    QList<Trip*> trips() const;
    TripState tripState() const;

public slots:
    void setPaths(QList<Path*> paths);
    void setCurrentPath(Path* currentPath);

    void setCurrentTrip(Trip* currentTrip);
    void setTrips(QList<Trip*> trips);
    void setTripState(TripState tripState);

signals:
    void pathsChanged(QList<Path*> paths);
    void currentPathChanged(Path* currentPath);

    void currentTripChanged(Trip* currentTrip);
    void tripsChanged(QList<Trip*> trips);
    void tripStateChanged(TripState tripState);

private:
    GeoPositioningController* m_geoController;
    DbController* m_database;
    QList<Path*> m_paths;
    Path* m_currentPath;

    Trip* m_currentTrip;
    QList<Trip*> m_trips;
    TripState m_tripState;
};

#endif // TRAVELCONTROLLER_H
