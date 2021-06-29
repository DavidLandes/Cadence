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


signals:

private:
    bool connectDatabase();

    TripDao* m_tripDao;
    PositionDao* m_positionDao;

};

#endif // DBCONTROLLER_H
