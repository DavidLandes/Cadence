#ifndef GEOPOSITIONINGCONTROLLER_H
#define GEOPOSITIONINGCONTROLLER_H

#include "./header/DbController.h"
#include "./header/DeviceInterface.h"

#include <QObject>
#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>
#include <QGeoCoordinate>
#include <QTimer>

class GeoPositioningController : public QObject
{
    Q_OBJECT
public:
    explicit GeoPositioningController(DeviceInterface* cadence, QObject *parent = nullptr);
    ~GeoPositioningController();

    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)

    enum class State {
        Inactive,
        Active
    }; Q_ENUM(State)

    // Start/Stop the satellite updates.
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    State state() const;

public slots:
    void setState(State state);

signals:
    void stateChanged(State state);
    void positionUpdated(QGeoPositionInfo coordinate, double velocityMph);

private:
    DeviceInterface* m_cadence;
    QGeoPositionInfoSource* m_positioningSource;
    State m_state;
};

#endif // GEOPOSITIONINGCONTROLLER_H
