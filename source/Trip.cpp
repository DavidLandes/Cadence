#include "./header/Trip.h"

Trip::Trip(QObject *parent) : QObject(parent)
{

}

int Trip::tripId() const
{
    return m_tripId;
}

QString Trip::name() const
{
    return m_name;
}

QDateTime Trip::startTime() const
{
    return m_startTime;
}

QDateTime Trip::endTime() const
{
    return m_endTime;
}

QList<Position *> Trip::positions() const
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

void Trip::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
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

void Trip::setPositions(QList<Position *> positions)
{
    if (m_positions == positions)
        return;

    m_positions = positions;
    emit positionsChanged(m_positions);
}
