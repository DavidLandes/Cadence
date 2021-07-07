#pragma once
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

#include "DeviceInterface.h"
#include "BluetoothController.h"
#include "BluetoothFrames.h"
#include "Device.h"
#include "DbController.h"
#include "Trip.h"
#include "TripDao.h"
#include "Position.h"
#include "PositionDao.h"
#include "GeoPositioningController.h"
#include "NotificationData.h"
#include "NotificationController.h"

/* Cadence Sensor Important Info:
 *  Red light - wheel data
 * Blue light - crank data
*/

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Create app configuration file.
    QSettings* settings = new QSettings("./cadence.conf");

    // Register controllers.
    BluetoothController* blControl = new BluetoothController(settings);
    DbController* databaseController = new DbController();

    // Register devices.
    DeviceInterface* cadenceInterface = new DeviceInterface(blControl, settings);

    // Register positioning controller.
    GeoPositioningController* geoController = new GeoPositioningController(databaseController, cadenceInterface);

    // Register notification controller.
    NotificationController* notifications = new NotificationController();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Expose properties to qml.
    engine.rootContext()->setContextProperty("blController", blControl);
    engine.rootContext()->setContextProperty("cadenceInterface", cadenceInterface);
    engine.rootContext()->setContextProperty("geoController", geoController);
    engine.rootContext()->setContextProperty("notifications", notifications);

    // Register types to qml.
    qmlRegisterUncreatableType<BluetoothController>("com.Cadence.BluetoothController", 1, 0, "BluetoothController", "bl controller reason");
    qmlRegisterUncreatableType<Device>("com.Cadence.Types", 1, 0, "Device", "device reason");
    qmlRegisterUncreatableType<Trip>("com.Cadence.Types", 1, 0, "Trip", "trip reason");
    qmlRegisterUncreatableType<Position>("com.Cadence.Types", 1, 0, "Position", "position reason");
    qmlRegisterUncreatableType<NotificationController>("com.Cadence.Types", 1, 0, "NotificationController", "notification controller reason");
    qmlRegisterUncreatableType<NotificationData>("com.Cadence.Types", 1, 0, "NotificationData", "notification data reason");



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
