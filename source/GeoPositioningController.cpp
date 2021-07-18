#include "./header/GeoPositioningController.h"

#include <QDebug>

#define UPDATE_INTERVAL 3*1000

GeoPositioningController::GeoPositioningController(DeviceInterface* cadence, QObject *parent) : QObject(parent)
  , m_cadence(cadence)
{
    qDebug() << QGeoPositionInfoSource::availableSources();
    m_positioningSource = QGeoPositionInfoSource::createDefaultSource(0);
    if (!m_positioningSource) qDebug() << "No positioning source on this device.";

    m_positioningSource->setUpdateInterval(UPDATE_INTERVAL);
}

GeoPositioningController::~GeoPositioningController()
{
    delete m_positioningSource;
}

void GeoPositioningController::start()
{
//    if (trip == nullptr && m_currentTrip == nullptr)
//    {
//        // Invalid input, can't start trip.
//        return;
//    }
//    else if (trip == nullptr && m_currentTrip != nullptr)
//    {
//        // Resume current trip.
//        trip = m_currentTrip;
//    }
//    // Else start the provided trip.

    setState(State::Active);

    m_positioningSource->startUpdates();
    connect(m_positioningSource, &QGeoPositionInfoSource::positionUpdated, this, [=](QGeoPositionInfo pos){
        emit positionUpdated(pos, m_cadence->mph());
    });
}

void GeoPositioningController::stop()
{
    setState(State::Inactive);

    m_positioningSource->stopUpdates();
    disconnect(m_positioningSource, &QGeoPositionInfoSource::positionUpdated, nullptr, nullptr);
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
