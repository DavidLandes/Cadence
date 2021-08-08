#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include "./header/Position.h"
#include "./header/Trip.h"
#include "./header/Path.h"
#include "./header/PositionDao.h"
#include "./header/TripDao.h"
#include "./header/PathDao.h"

#include <QObject>

class DbController : public QObject
{
    Q_OBJECT
public:
    explicit DbController(QObject *parent = nullptr);
    ~DbController();

    // Returns the saved item.
    Trip* saveTrip(QString name, int pathId, QDateTime startTime, QDateTime endTime);
    Path* savePath(QString name);
    void savePosition(int tripId, QDateTime timestamp, double latitude, double longitude, double velocityMph);

    Trip* getTrip(int tripId);
    Path* getPath(int pathId);
    QList<Trip*> getAllTrips();
    QList<Path*> getAllPaths();

    void deleteTrip(int tripId);
    void deletePath(int pathId);

    void deleteAll();

signals:

private:
    bool connectDatabase();

    // Remove Positions from the database that do not belong to a Trip.
    void clean();

    PathDao* m_pathDao;
    TripDao* m_tripDao;
    PositionDao* m_positionDao;
};

#endif // DBCONTROLLER_H
