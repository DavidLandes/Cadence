#include "./header/DbController.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

DbController::DbController(QObject *parent) : QObject(parent)
{
    connectDatabase();
    m_tripDao = new TripDao();
    m_positionDao = new PositionDao();
    m_pathDao = new PathDao();
    clean();
}

DbController::~DbController()
{
    delete m_tripDao;
    delete m_positionDao;
    delete m_pathDao;
}

Trip* DbController::saveTrip(QString name, QDateTime startTime, QDateTime endTime)
{
    return m_tripDao->saveTrip(name, startTime, endTime);
}

Path* DbController::savePath(QString name)
{
    return m_pathDao->savePath(name);
}

void DbController::savePosition(int tripId, QDateTime timestamp, double latitude, double longitude, double velocityMph)
{
    m_positionDao->savePosition(tripId, timestamp, latitude, longitude, velocityMph);
}

QList<Trip *> DbController::getAllTrips()
{
    QList<Trip*> trips = m_tripDao->getAll();

    for (Trip* t : trips)
    {
        t->setPositions(m_positionDao->getPositionsFromTrip(t->tripId()));
    }

    return trips;
}

QList<Path*> DbController::getAllPaths()
{
    return m_pathDao->getAll();
}

void DbController::deleteTrip(int tripId)
{
    m_tripDao->deleteTrip(tripId);
    m_positionDao->deletePositions(tripId);
}

void DbController::deletePath(int pathId)
{
    m_pathDao->deletePath(pathId);
}

void DbController::deleteAll()
{
    m_pathDao->deleteAll();
    m_tripDao->deleteAll();
    m_positionDao->deleteAll();
}

bool DbController::connectDatabase()
{
    QString driver("QSQLITE");

    if (QSqlDatabase::isDriverAvailable(driver))
    {
        QSqlDatabase database = QSqlDatabase::addDatabase(driver);
        database.setDatabaseName("CadenceGps");

        if (!database.open())
        {
            qWarning() << "Database connection error - " << database.lastError().text();
        }
        else
        {
            qDebug() << "Database initialized - Success";
            return true;
        }
    }
    else
    {
        qWarning() << "Database connection Error - No Driver" << driver << "available.";
    }
    return false;
}

void DbController::clean()
{
    QList<Trip*> trips = m_tripDao->getAll();
    QString idList = "";

    for (int i = 0; i < trips.length(); i++)
    {
        // If this is the first item...
        if (i == 0)
        {
            idList.append("(");
        }

        idList.append(QString::number(trips[i]->tripId()));

        // If there are more ids left...
        if (i < trips.length() - 1)
        {
            idList.append(", ");
        }
        else
        {
            idList.append(")");
        }
    }

    QString clean = "DELETE FROM Positions WHERE TripId NOT IN " + idList;

    QSqlQuery query;
    query.prepare(clean);

    bool success = query.exec();
    qDebug() << "DbController::clean() -" << (success ? "Success" : "Clean Unnecessary");
}

