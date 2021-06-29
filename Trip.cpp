#include "Trip.h"

Trip::Trip(QObject *parent) : QObject(parent)
{

}

int Trip::tripId() const
{
    return m_tripId;
}

QString Trip::tripName() const
{
    return m_tripName;
}

QDateTime Trip::startTime() const
{
    return m_startTime;
}

QDateTime Trip::endTime() const
{
    return m_endTime;
}

QList<QObject *> Trip::positions() const
{
    return m_positions;
}

void Trip::setTripId(int tripId)
{
    if (m_tripId == tripId)
        return;

    m_tripId = tripId;
    emit tripIdChanged(m_tripId);
}

void Trip::setTripName(QString tripName)
{
    if (m_tripName == tripName)
        return;

    m_tripName = tripName;
    emit tripNameChanged(m_tripName);
}

void Trip::setStartTime(QDateTime startTime)
{
    if (m_startTime == startTime)
        return;

    m_startTime = startTime;
    emit startTimeChanged(m_startTime);
}

void Trip::setEndTime(QDateTime endTime)
{
    if (m_endTime == endTime)
        return;

    m_endTime = endTime;
    emit endTimeChanged(m_endTime);
}

void Trip::setPositions(QList<QObject *> positions)
{
    if (m_positions == positions)
        return;

    m_positions = positions;
    emit positionsChanged(m_positions);
}
