#ifndef POSITIONDAO_H
#define POSITIONDAO_H

#include "Position.h"

#include <QObject>
#include <QSqlQuery>
#include <QGeoCoordinate>

class PositionDao : public QObject
{
    Q_OBJECT
public:
    explicit PositionDao(QObject *parent = nullptr);

    void savePosition(int tripId, QDateTime timestamp, double latitude, double longitude, double velocityMph);
    QList<Position*> getPositionsFromTrip(int tripId);
    Position* getPosition(int positionId);
    void deletePositions(int tripId);
    Position* toEntity(QSqlQuery query);

signals:

};

#endif // POSITIONDAO_H
