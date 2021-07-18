#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include "./header/Position.h"
#include "./header/Trip.h"
#include "./header/PositionDao.h"
#include "./header/TripDao.h"

#include <QObject>

class DbController : public QObject
{
    Q_OBJECT
public:
    explicit DbController(QObject *parent = nullptr);
    ~DbController();

    // Returns the saved item.
    Trip* saveTrip(QString name, QDateTime startTime, QDateTime endTime);
    void savePosition(int tripId, QDateTime timestamp, double latitude, double longitude, double velocityMph);
    QList<Trip*> getAllTrips();
    void deleteTrip(int tripId);

    void deleteAll();

signals:

private:
    bool connectDatabase();

    // Remove Positions from the database that do not belong to a Trip.
    void clean();

    TripDao* m_tripDao;
    PositionDao* m_positionDao;
};

#endif // DBCONTROLLER_H
