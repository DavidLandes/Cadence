#include "GeoPositioningController.h"

#include <QDebug>

#define UPDATE_INTERVAL 2*1000

GeoPositioningController::GeoPositioningController(DbController* dbControl, DeviceInterface* cadence, QObject *parent) : QObject(parent)
  , m_database(dbControl)
  , m_cadence(cadence)
  , m_currentTrip(nullptr)
{
    qDebug() << QGeoPositionInfoSource::availableSources();
    m_positioningSource = QGeoPositionInfoSource::createDefaultSource(0);
    if (!m_positioningSource) qDebug() << "No positioning source on this device.";

    m_positioningSource->setUpdateInterval(UPDATE_INTERVAL);

    // Load Trips from the database when the app starts.
    setTrips(m_database->getAllTrips());

}

GeoPositioningController::~GeoPositioningController()
{
    delete m_positioningSource;
}

void GeoPositioningController::start(Trip* trip)
{
    m_positioningSource->startUpdates();
    setCurrentTrip(trip);
    connect(m_positioningSource, &QGeoPositionInfoSource::positionUpdated, this, &GeoPositioningController::logPosition);
}

void GeoPositioningController::stop()
{
    m_positioningSource->stopUpdates();
    setCurrentTrip(nullptr);
    disconnect(m_positioningSource, &QGeoPositionInfoSource::positionUpdated, this, &GeoPositioningController::logPosition);
}

void GeoPositioningController::createTrip(QString name, QDateTime startTime, QDateTime endTime)
{
    Trip* newTrip = m_database->saveTrip(name, startTime, endTime);
    m_trips.append(newTrip);
    emit tripsChanged(m_trips);
}

void GeoPositioningController::deleteTrip(Trip* trip)
{
    if (trip == m_currentTrip)
    {
        stop();
    }

    // Delete Trip from database.
    m_database->deleteTrip(trip->tripId());
    m_trips.removeAt(m_trips.indexOf(trip));
    emit tripsChanged(m_trips);

    // Free memory.
    for (Position* p : trip->positions())
    {
        p = nullptr;
        delete p;
    }
    trip = nullptr;
    delete trip;

}

void GeoPositioningController::logPosition(QGeoPositionInfo geo)
{
    if (m_currentTrip != nullptr)
    {
        if (geo.isValid())
        {
            Position* pos = new Position();
            pos->setTripId(currentTrip()->tripId());
            pos->setTimestamp(geo.timestamp());
            pos->setLatitude(geo.coordinate().latitude());
            pos->setLongitude(geo.coordinate().longitude());
            pos->setVelocityMph(m_cadence->mph());

            m_database->savePosition(pos->tripId(), pos->timestamp(), pos->latitude(), pos->longitude(), pos->velocityMph());
            m_currentTrip->positions().append(pos);
            emit currentTripChanged(m_currentTrip);
            emit tripsChanged(m_trips);
        }
        else
        {
            qDebug() << "Could not log position. Last known coordinate was invalid.";
        }
    }
    else
    {
        stop();
        qDebug() << "Could not log position. There is no active trip.";
    }
}

Trip *GeoPositioningController::currentTrip() const
{
    return m_currentTrip;
}

QList<Trip *> GeoPositioningController::trips() const
{
    return m_trips;
}

void GeoPositioningController::setCurrentTrip(Trip *currentTrip)
{
    if (m_currentTrip == currentTrip)
        return;

    m_currentTrip = currentTrip;
    emit currentTripChanged(m_currentTrip);
}

void GeoPositioningController::setTrips(QList<Trip *> trips)
{
    if (m_trips == trips)
        return;

//    // Clear the existing list data.
//    for (Trip* t : m_trips)
//    {
//        // Free memory.
//        for (Position* p : t->positions())
//        {
//            p = nullptr;
//            delete p;
//        }
//        t = nullptr;
//        delete t;
//    }

    m_trips = trips;
    emit tripsChanged(m_trips);
}
