#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include "Position.h"
#include "Trip.h"
#include "PositionDao.h"
#include "TripDao.h"

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

signals:

private:
    bool connectDatabase();

    // Remove Positions from the database that do not belong to a Trip.
    void cleanDatabase();

    TripDao* m_tripDao;
    PositionDao* m_positionDao;
};

#endif // DBCONTROLLER_H
