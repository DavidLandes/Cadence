#ifndef TRIP_H
#define TRIP_H

#include "./header/Position.h"

#include <QObject>
#include <QDateTime>

class Trip : public QObject
{
    Q_OBJECT
public:
    explicit Trip(QObject *parent = nullptr);

    Q_PROPERTY(int tripId READ tripId WRITE setTripId NOTIFY tripIdChanged)
    Q_PROPERTY(QString tripName READ tripName WRITE setTripName NOTIFY tripNameChanged)
    Q_PROPERTY(QDateTime startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged)
    Q_PROPERTY(QDateTime endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged)
    Q_PROPERTY(QList<Position*> positions READ positions WRITE setPositions NOTIFY positionsChanged)

    int tripId() const;
    QString tripName() const;
    QDateTime startTime() const;
    QDateTime endTime() const;    
    QList<Position*> positions() const;

public slots:
    void setTripId(int tripId);
    void setTripName(QString tripName);
    void setStartTime(QDateTime startTime);
    void setEndTime(QDateTime endTime);    
    void setPositions(QList<Position*> positions);

signals:
    void tripIdChanged(int tripId);
    void tripNameChanged(QString tripName);
    void startTimeChanged(QDateTime startTime);
    void endTimeChanged(QDateTime endTime);    
    void positionsChanged(QList<Position*> positions);

private:
    int m_tripId;
    QString m_tripName;
    QDateTime m_startTime;
    QDateTime m_endTime;    
    QList<Position*> m_positions;
};

#endif // TRIP_H
