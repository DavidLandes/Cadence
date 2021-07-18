#include "./header/PathDao.h"

#include <QDebug>

PathDao::PathDao(QObject *parent) : QObject(parent)
{
    QString create_table = "CREATE TABLE IF NOT EXISTS Paths ("
                           "PathId INTEGER,"
                           "Name TEXT,"
                           "PRIMARY KEY(PathId AUTOINCREMENT)"
                           ")";

    QSqlQuery query;
    query.prepare(create_table);

    qDebug() << "Path Dao Create Table -" << (query.exec() ? "Success" : "Failed");
}

Path* PathDao::savePath(QString name)
{
    QString save = "INSERT INTO Paths ("
            "Name)"
            " VALUES ("
            ":name)";

    QSqlQuery query;
    query.prepare(save);
    query.bindValue(":name", name);

    bool success = query.exec();
    qDebug() << "PathDao::savePath() -" << (success ? "Success" : "Failed");
    return lastRecord();
}

Path* PathDao::getPath(int pathId)
{
    QString get = "SELECT * FROM Paths "
           "WHERE PathId=:pathid";

    QSqlQuery query;
    query.prepare(get);
    query.bindValue(":pathid", pathId);

    bool success = query.exec();
    qDebug() << "PathDao::getPath() -" << (success ? "Success" : "Failed");

    query.first();
    return toEntity(query);
}

QList<Path*> PathDao::getAll()
{
    QString get = "SELECT * FROM Paths "
           "WHERE 1=1";

    QSqlQuery query;
    query.prepare(get);

    bool success = query.exec();
    qDebug() << "PathDao::getAll() -" << (success ? "Success" : "Failed");

    QList<Path*> paths;
    while(query.next())
    {
        paths.append(toEntity(query));
    }

    return paths;
}

void PathDao::deletePath(int pathId)
{
    QString del = "DELETE FROM Paths"
            " WHERE PathId=:pathid";

    QSqlQuery query;
    query.prepare(del);
    query.bindValue(":pathid", pathId);

    bool success = query.exec();
    qDebug() << "PathDao::deletePath() -" << (success ? "Success" : "Failed");
}

void PathDao::deleteAll()
{
    QString del = "DELETE FROM Paths"
                  " WHERE 1=1";

    QSqlQuery query;
    query.prepare(del);

    bool success = query.exec();
    qDebug() << "PathDao::deleteAll() -" << (success ? "Success" : "Failed");
}

Path* PathDao::toEntity(QSqlQuery query)
{
    if (query.result() != nullptr)
    {
        Path* path = new Path();

        path->setPathId(query.value("PathId").toInt());
        path->setName(query.value("Name").toString());

        return path;
    }
    else
    {
        qDebug() << "PathDao::toEntity() - Cannot Parse query";
    }
    return nullptr;
}

Path *PathDao::lastRecord()
{
    QString last = "SELECT * FROM Paths"
            " ORDER BY PathId DESC LIMIT 1";

    QSqlQuery query;
    query.prepare(last);

    bool success = query.exec();
    qDebug() << "PathDao::lastRecord() -" << (success ? "Success" : "Failed");

    query.first();
    return toEntity(query);
}
