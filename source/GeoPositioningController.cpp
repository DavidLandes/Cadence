#include "./header/GeoPositioningController.h"

#include <QDebug>

#define UPDATE_INTERVAL 3*1000

GeoPositioningController::GeoPositioningController(DbController* dbControl, DeviceInterface* cadence, QObject *parent) : QObject(parent)
  , m_database(dbControl)
  , m_cadence(cadence)
  , m_currentTrip(nullptr)
{
    qDebug() << QGeoPositionInfoSource::availableSources();
 //   m_positioningSource = QGeoPositionInfoSource::createDefaultSource(0);
  //  if (!m_positioningSource) qDebug() << "No positioning source on this device.";

 //   m_positioningSource->setUpdateInterval(UPDATE_INTERVAL);

    // Load Trips from the database when the app starts.
    setTrips(m_database->getAllTrips());

}

GeoPositioningController::~GeoPositioningController()
{
   // delete m_positioningSource;
}

void GeoPositioningController::start(Trip* trip)
{
    if (trip == nullptr && m_currentTrip == nullptr)
    {
        // Invalid input, can't start trip.
        return;
    }
    else if (trip == nullptr && m_currentTrip != nullptr)
    {
        // Resume current trip.
        trip = m_currentTrip;
    }
    // Else start the provided trip.

    setTripState(TripState::Active);
    setCurrentTrip(trip);
  //  m_positioningSource->startUpdates();
  //  connect(m_positioningSource, &QGeoPositionInfoSource::positionUpdated, this, &GeoPositioningController::logPosition);
}

void GeoPositioningController::stop()
{
    setTripState(TripState::Inactive);
  //  m_positioningSource->stopUpdates();
  //  disconnect(m_positioningSource, &QGeoPositionInfoSource::positionUpdated, this, &GeoPositioningController::logPosition);
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

void GeoPositioningController::deleteAllTripData()
{
    m_database->deleteAll();
    for (Trip* t : m_trips)
    {
        // Free memory.
        for (Position* p : t->positions())
        {
            p = nullptr;
            delete p;
        }
        t = nullptr;
        delete t;
    }
    setCurrentTrip(nullptr);
    m_trips.clear();
    emit tripsChanged(m_trips);
}

void GeoPositioningController::logPosition(QGeoPositionInfo geo)
{
    if (m_currentTrip != nullptr)
    {
        if (geo.isValid()/* && TODO: If position is waaaay off, don't log it. Need lati,long threshold*/)
        {
            Position* pos = new Position();
            pos->setTripId(currentTrip()->tripId());
            pos->setTimestamp(geo.timestamp());
            pos->setCoordinate(geo.coordinate());
            pos->setVelocityMph(m_cadence->mph());

            m_database->savePosition(pos->tripId(), pos->timestamp(), pos->coordinate().latitude(), pos->coordinate().longitude(), pos->velocityMph());

            // Update positions so updates are signaled.
            QList<Position*> tempPositions = m_currentTrip->positions();
            tempPositions.append(pos);
            m_currentTrip->setPositions(tempPositions);

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

GeoPositioningController::TripState GeoPositioningController::tripState() const
{
    return m_tripState;
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

void GeoPositioningController::setTripState(GeoPositioningController::TripState tripState)
{
    if (m_tripState == tripState)
        return;

    m_tripState = tripState;
    emit tripStateChanged(m_tripState);
}
