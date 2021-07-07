#include "PositionDao.h"

#include <QDebug>

PositionDao::PositionDao(QObject *parent) : QObject(parent)
{
    QString create_table = "CREATE TABLE IF NOT EXISTS Positions ("
                           "PositionId INTEGER,"
                           "TripId INTEGER,"
                           "Timestamp TEXT,"
                           "Latitude REAL,"
                           "Longitude REAL,"
                           "VelocityMph REAL,"
                           "PRIMARY KEY(PositionId AUTOINCREMENT)"
                           ")";

    QSqlQuery query;
    query.prepare(create_table);

    qDebug() << "Position Dao Create Table -" << (query.exec() ? "Success" : "Failed");

//    savePosition(4, QDateTime::currentDateTime(), 34.543, 76.22, 21.33);
//    getPosition(2);
//    getPositionsFromTrip(4);

}

void PositionDao::savePosition(int tripId, QDateTime timestamp, double latitude, double longitude, double velocityMph)
{
    QString save = "INSERT INTO Positions ("
            "TripId,"
            "Timestamp,"
            "Latitude,"
            "Longitude,"
            "VelocityMph)"
            " VALUES ("
            ":tripid,"
            ":timestamp,"
            ":latitude,"
            ":longitude,"
            ":velocityMph"
            ")";

    QSqlQuery query;
    query.prepare(save);
    query.bindValue(":tripid", tripId);
    query.bindValue(":timestamp", timestamp.toString());
    query.bindValue(":latitude", latitude);
    query.bindValue(":longitude", longitude);
    query.bindValue(":velocityMph", velocityMph);

    bool success = query.exec();
    qDebug() << "PositionDao::savePosition() -" << (success ? "Success" : "Failed");
}

QList<Position*> PositionDao::getPositionsFromTrip(int tripId)
{
    QString get = "SELECT * FROM Positions "
           "WHERE TripId=:tripid";

    QSqlQuery query;
    query.prepare(get);
    query.bindValue(":tripid", tripId);

    bool success = query.exec();
    qDebug() << "PositionDao::getPositionFromTrip() -" << (success ? "Success" : "Failed");

    QList<Position*> tripPositions;
    while(query.next())
    {
        tripPositions.append(toEntity(query));
    }

    return tripPositions;
}

Position* PositionDao::getPosition(int positionId)
{
    QString get = "SELECT * FROM Positions "
           "WHERE PositionId=:positionid";

    QSqlQuery query;
    query.prepare(get);
    query.bindValue(":positionid", positionId);

    bool success = query.exec();
    qDebug() << "PositionDao::getPosition() -" << (success ? "Success" : "Failed");

    query.first();
    return toEntity(query);
}

void PositionDao::deletePositions(int tripId)
{
    QString del = "DELETE FROM Positions"
                  " WHERE TripId=:tripid";

    QSqlQuery query;
    query.prepare(del);
    query.bindValue(":tripid", tripId);

    bool success = query.exec();
    qDebug() << "PositionDao::deletePositions() -" << (success ? "Success" : "Failed");
}

Position* PositionDao::toEntity(QSqlQuery query)
{
    if (query.result() != nullptr)
    {
        Position* pos = new Position();

        pos->setPositionId(query.value("PositionId").toInt());
        pos->setTripId(query.value("TripId").toInt());
        pos->setTimestamp(query.value("Timestamp").toDateTime());
        pos->setCoordinate(QGeoCoordinate(query.value("Latitude").toDouble(), query.value("Longitude").toDouble()));
        pos->setVelocityMph(query.value("VelocityMph").toDouble());

        return pos;
    }
    else
    {
        qDebug() << "PositionDao::toEntity() - Cannot Parse query";
    }
    return nullptr;
}
