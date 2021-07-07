#ifndef POSITION_H
#define POSITION_H

#include <QObject>
#include <QDateTime>
#include <QGeoCoordinate>

class Position : public QObject
{
    Q_OBJECT

public:
    explicit Position(QObject *parent = nullptr);

    Q_PROPERTY(int positionId READ positionId WRITE setPositionId NOTIFY positionIdChanged)
    Q_PROPERTY(int tripId READ tripId WRITE setTripId NOTIFY tripIdChanged)
    Q_PROPERTY(QDateTime timestamp READ timestamp WRITE setTimestamp NOTIFY timestampChanged)
    Q_PROPERTY(double velocityMph READ velocityMph WRITE setVelocityMph NOTIFY velocityMphChanged)
    Q_PROPERTY(QGeoCoordinate coordinate READ coordinate WRITE setCoordinate NOTIFY coordinateChanged)

    double velocityMph() const;
    int positionId() const;
    int tripId() const;
    QDateTime timestamp() const;
    QGeoCoordinate coordinate() const;

public slots:
    void setVelocityMph(double velocityMph);
    void setPositionId(int positionId);
    void setTripId(int tripId);
    void setTimestamp(QDateTime timestamp);
    void setCoordinate(QGeoCoordinate coordinate);

signals:
    void velocityMphChanged(double velocityMph);
    void positionIdChanged(int positionId);
    void tripIdChanged(int tripId);
    void timestampChanged(QDateTime timestamp);
    void coordinateChanged(QGeoCoordinate coordinate);

private:
    double m_velocityMph;
    int m_positionId;
    int m_tripId;
    QDateTime m_timestamp;
    QGeoCoordinate m_coordinate;
};

#endif // POSITION_H
