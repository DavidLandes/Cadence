#include "DbController.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

DbController::DbController(QObject *parent) : QObject(parent)
{
    connectDatabase();
    m_tripDao = new TripDao();
    m_positionDao = new PositionDao();
}

DbController::~DbController()
{
    delete m_tripDao;
    delete m_positionDao;
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

