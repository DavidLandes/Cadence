#include "./header/TravelController.h"

TravelController::TravelController(DbController* database, GeoPositioningController* geoController, QObject *parent) : QObject(parent)
  , m_geoController(geoController)
  , m_database(database)
  , m_currentPath(nullptr)
  , m_currentTrip(nullptr)
{
    setPaths(m_database->getAllPaths());
    setTrips(m_database->getAllTrips());

    connect(m_geoController, &GeoPositioningController::positionUpdated, this, &TravelController::logPosition);
}

void TravelController::createPath(QString name)
{
    m_database->savePath(name);

    Path* newPath = m_database->savePath(name);
    m_paths.append(newPath);
    emit pathsChanged(m_paths);
}

void TravelController::deletePath(Path* path)
{
    m_database->deletePath(path->pathId());

    m_paths.removeAt(m_paths.indexOf(path));
    emit pathsChanged(m_paths);
}

void TravelController::createTrip(QString name, int pathId, QDateTime startTime, QDateTime endTime, bool setAsCurrentTrip)
{
    Trip* newTrip = m_database->saveTrip(name, pathId, startTime, endTime);
    m_trips.append(newTrip);
    emit tripsChanged(m_trips);

    if (setAsCurrentTrip)
    {
        setCurrentTrip(newTrip);
    }
}

void TravelController::deleteTrip(Trip* trip)
{
    if (trip == m_currentTrip)
    {
        m_geoController->stop();
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

void TravelController::logPosition(QGeoPositionInfo geo, double velocityMph)
{
    if (m_currentTrip != nullptr)
    {
        if (geo.isValid()/* && TODO: If position is waaaay off, don't log it. Need lati,long threshold*/)
        {
            Position* pos = new Position();
            pos->setTripId(currentTrip()->tripId());
            pos->setTimestamp(geo.timestamp());
            pos->setCoordinate(geo.coordinate());
            pos->setVelocityMph(velocityMph);

            m_database->savePosition(pos->tripId(), pos->timestamp(), pos->coordinate().latitude(), pos->coordinate().longitude(), pos->velocityMph());

            // Update positions so updates are signaled.
            QList<Position*> tempPositions = m_currentTrip->positions();
            tempPositions.append(pos);
            m_currentTrip->setPositions(tempPositions);

            emit currentTripChanged(m_currentTrip);
            emit tripsChanged(m_trips);
            qDebug() << "Logging Position";
        }
        else
        {
            qDebug() << "Could not log position. Last known coordinate was invalid.";
        }
    }
    else
    {
        m_geoController->stop();
        qDebug() << "Could not log position. There is no active trip.";
    }

}

QList<Path *> TravelController::paths() const
{
    return m_paths;
}

Path *TravelController::currentPath() const
{
    return m_currentPath;
}

void TravelController::setPaths(QList<Path *> paths)
{
    if (m_paths == paths)
        return;

    m_paths = paths;
    emit pathsChanged(m_paths);
}

void TravelController::setCurrentPath(Path *currentPath)
{
    if (m_currentPath == currentPath)
        return;

    m_currentPath = currentPath;
    emit currentPathChanged(m_currentPath);
}

Trip *TravelController::currentTrip() const
{
    return m_currentTrip;
}

QList<Trip *> TravelController::trips() const
{
    return m_trips;
}

void TravelController::setCurrentTrip(Trip *currentTrip)
{
    if (m_currentTrip == currentTrip)
        return;

    m_currentTrip = currentTrip;
    emit currentTripChanged(m_currentTrip);
}

void TravelController::setTrips(QList<Trip *> trips)
{
    if (m_trips == trips)
        return;

    m_trips = trips;
    emit tripsChanged(m_trips);
}
