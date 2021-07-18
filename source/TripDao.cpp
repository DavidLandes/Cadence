#include "./header/TripDao.h"

#include <QDebug>

TripDao::TripDao(QObject *parent) : QObject(parent)
{
    QString create_table = "CREATE TABLE IF NOT EXISTS Trips ("
                           "TripId INTEGER,"
                           "TripName TEXT,"
                           "StartTime TEXT,"
                           "EndTime TEXT,"
                           "PRIMARY KEY(TripId AUTOINCREMENT)"
                           ")";

    QSqlQuery query;
    query.prepare(create_table);

    qDebug() << "Trip Dao Create Table -" << (query.exec() ? "Success" : "Failed");

//    saveTrip("testtrip", QDateTime::currentDateTime(), QDateTime::currentDateTime().addDays(1));
//    saveTrip("testtrip", QDateTime::currentDateTime(), QDateTime::currentDateTime().addDays(1));
//    getTrip(2);

}

Trip* TripDao::saveTrip(QString name, QDateTime startTime, QDateTime endTime)
{
    QString save = "INSERT INTO Trips ("
            "TripName,"
            "StartTime,"
            "EndTime)"
            " VALUES ("
            ":tripname,"
            ":starttime,"
            ":endtime"
            ")";

    QSqlQuery query;
    query.prepare(save);
    query.bindValue(":tripname", name);
    query.bindValue(":starttime", startTime.toString());
    query.bindValue(":endtime", endTime.toString());

    bool success = query.exec();
    qDebug() << "TripDao::saveTrip() -" << (success ? "Success" : "Failed");
    return lastRecord();
}

Trip *TripDao::getTrip(int tripId)
{
    QString get = "SELECT * FROM Trips"
            " WHERE TripId=:tripid";

    QSqlQuery query;
    query.prepare(get);
    query.bindValue(":tripid", tripId);

    bool success = query.exec();
    qDebug() << "TripDao::getTrip() -" << (success ? "Success" : "Failed");

    query.first();
    return toEntity(query);
}

QList<Trip *> TripDao::getAll()
{
    QList<Trip*> list;
    QString get = "SELECT * FROM Trips"
            " WHERE 1=1";

    QSqlQuery query;
    query.prepare(get);

    bool success = query.exec();
    qDebug() << "TripDao::getAll() -" << (success ? "Success" : "Failed");

    while(query.next())
    {
        list.append(toEntity(query));
    }

    return list;
}

void TripDao::deleteTrip(int tripId)
{
    QString del = "DELETE FROM Trips"
            " WHERE TripId=:tripid";

    QSqlQuery query;
    query.prepare(del);
    query.bindValue(":tripid", tripId);

    bool success = query.exec();
    qDebug() << "TripDao::deleteTrip() -" << (success ? "Success" : "Failed");
}

void TripDao::deleteAll()
{
    QString del = "DELETE FROM Trips"
            " WHERE 1=1";

    QSqlQuery query;
    query.prepare(del);

    bool success = query.exec();
    qDebug() << "TripDao::deleteAll() -" << (success ? "Success" : "Failed");
}

Trip *TripDao::toEntity(QSqlQuery query)
{
    if (query.result() != nullptr)
    {
        Trip* trip = new Trip();

        trip->setTripId(query.value("TripId").toInt());
        trip->setTripName(query.value("TripName").toString());
        trip->setStartTime(query.value("StartTime").toDateTime());
        trip->setEndTime(query.value("EndTime").toDateTime());

        return trip;
    }
    else
    {
        qDebug() << "TripDao::toEntity() - Cannot Parse query";
    }
    return nullptr;
}

Trip* TripDao::lastRecord()
{
    QString last = "SELECT * FROM Trips"
            " ORDER BY TripId DESC LIMIT 1";

    QSqlQuery query;
    query.prepare(last);

    bool success = query.exec();
    qDebug() << "TripDao::lastRecord() -" << (success ? "Success" : "Failed");

    query.first();
    return toEntity(query);
}
