#ifndef PATHDAO_H
#define PATHDAO_H

#include <QObject>
#include <QSqlQuery>

#include "./header/Path.h"

class PathDao : public QObject
{
    Q_OBJECT
public:
    explicit PathDao(QObject *parent = nullptr);

    Path* savePath(QString name);
    Path* getPath(int pathId);
    QList<Path*> getAll();
    void deletePath(int pathId);
    void deleteAll();
    Path* toEntity(QSqlQuery query);
signals:

private:
    Path* lastRecord();

};

#endif // PATHDAO_H
