#include "Position.h"

Position::Position(QObject *parent) : QObject(parent)
{

}

double Position::velocityMph() const
{
    return m_velocityMph;
}

int Position::positionId() const
{
    return m_positionId;
}

int Position::tripId() const
{
    return m_tripId;
}

QDateTime Position::timestamp() const
{
    return m_timestamp;
}

QGeoCoordinate Position::coordinate() const
{
    return m_coordinate;
}

void Position::setVelocityMph(double velocityMph)
{
    if (qFuzzyCompare(m_velocityMph, velocityMph))
        return;

    m_velocityMph = velocityMph;
    emit velocityMphChanged(m_velocityMph);
}

void Position::setPositionId(int positionId)
{
    if (m_positionId == positionId)
        return;

    m_positionId = positionId;
    emit positionIdChanged(m_positionId);
}

void Position::setTripId(int tripId)
{
    if (m_tripId == tripId)
        return;

    m_tripId = tripId;
    emit tripIdChanged(m_tripId);
}

void Position::setTimestamp(QDateTime timestamp)
{
    if (m_timestamp == timestamp)
        return;

    m_timestamp = timestamp;
    emit timestampChanged(m_timestamp);
}

void Position::setCoordinate(QGeoCoordinate coordinate)
{
    if (m_coordinate == coordinate)
        return;

    m_coordinate = coordinate;
    emit coordinateChanged(m_coordinate);
}
