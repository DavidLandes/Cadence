#include "./header/GeoPositioningController.h"

#include <QDebug>

#define UPDATE_INTERVAL 3*1000

GeoPositioningController::GeoPositioningController(DeviceInterface* cadence, QObject *parent) : QObject(parent)
  , m_cadence(cadence)
  , m_state(State::Inactive)
{
#ifndef WINDOWS
    qDebug() << QGeoPositionInfoSource::availableSources();
    m_positioningSource = QGeoPositionInfoSource::createDefaultSource(0);
    if (!m_positioningSource) qDebug() << "No positioning source on this device.";

    m_positioningSource->setUpdateInterval(UPDATE_INTERVAL);
#endif
}

GeoPositioningController::~GeoPositioningController()
{
#ifndef WINDOWS
    delete m_positioningSource;
#endif
}

void GeoPositioningController::start()
{
    setState(State::Active);
#ifndef WINDOWS
    m_positioningSource->startUpdates();
    connect(m_positioningSource, &QGeoPositionInfoSource::positionUpdated, this, [=](QGeoPositionInfo pos){
        emit positionUpdated(pos, m_cadence->mph());
    });
#endif
}

void GeoPositioningController::stop()
{
    setState(State::Inactive);
#ifndef WINDOWS
    m_positioningSource->stopUpdates();
    disconnect(m_positioningSource, &QGeoPositionInfoSource::positionUpdated, nullptr, nullptr);
#endif
}

GeoPositioningController::State GeoPositioningController::state() const
{
    return m_state;
}

void GeoPositioningController::setState(GeoPositioningController::State state)
{
    if (m_state == state)
        return;

    m_state = state;
    emit stateChanged(m_state);
}
