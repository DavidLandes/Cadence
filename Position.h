#ifndef POSITION_H
#define POSITION_H

#include <QObject>
#include <QDateTime>

class Position : public QObject
{
    Q_OBJECT

public:
    explicit Position(QObject *parent = nullptr);

    Q_PROPERTY(int positionId READ positionId WRITE setPositionId NOTIFY positionIdChanged)
    Q_PROPERTY(int tripId READ tripId WRITE setTripId NOTIFY tripIdChanged)
    Q_PROPERTY(QDateTime timestamp READ timestamp WRITE setTimestamp NOTIFY timestampChanged)
    Q_PROPERTY(double latitude READ latitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(double longitude READ longitude WRITE setLongitude NOTIFY longitudeChanged)
    Q_PROPERTY(double velocityMph READ velocityMph WRITE setVelocityMph NOTIFY velocityMphChanged)

    double velocityMph() const;
    int positionId() const;
    int tripId() const;
    QDateTime timestamp() const;
    double latitude() const;
    double longitude() const;

public slots:
    void setVelocityMph(double velocityMph);
    void setPositionId(int positionId);
    void setTripId(int tripId);
    void setTimestamp(QDateTime timestamp);
    void setLatitude(double latitude);
    void setLongitude(double longitude);

signals:
    void velocityMphChanged(double velocityMph);
    void positionIdChanged(int positionId);
    void tripIdChanged(int tripId);
    void timestampChanged(QDateTime timestamp);
    void latitudeChanged(double latitude);
    void longitudeChanged(double longitude);

private:
    double m_velocityMph;
    int m_positionId;
    int m_tripId;
    QDateTime m_timestamp;
    double m_latitude;
    double m_longitude;

};

#endif // POSITION_H
