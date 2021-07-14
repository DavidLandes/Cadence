#pragma once
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

#include "misc.h"
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
#include "ExportController.h"

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

    ExportController* exportController = new ExportController();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    // Register types to qml.
    qmlRegisterUncreatableType<BluetoothController>("com.Cadence.BluetoothController", 1, 0, "BluetoothController", "bl controller reason");
    qmlRegisterUncreatableType<Device>("com.Cadence.Types", 1, 0, "Device", "device reason");
    qmlRegisterUncreatableType<Trip>("com.Cadence.Types", 1, 0, "Trip", "trip reason");
    qmlRegisterUncreatableType<Position>("com.Cadence.Types", 1, 0, "Position", "position reason");
    qmlRegisterUncreatableType<NotificationController>("com.Cadence.Types", 1, 0, "NotificationController", "notification controller reason");
    qmlRegisterUncreatableType<NotificationData>("com.Cadence.Types", 1, 0, "NotificationData", "notification data reason");
    qmlRegisterUncreatableType<GeoPositioningController>("com.Cadence.Types", 1, 0, "GeoPositioningController", "geo positioning controller reason");

    // Expose properties to qml.
    engine.rootContext()->setContextProperty("blController", blControl);
    engine.rootContext()->setContextProperty("cadenceInterface", cadenceInterface);
    engine.rootContext()->setContextProperty("geoController", geoController);
    engine.rootContext()->setContextProperty("notifications", notifications);
    engine.rootContext()->setContextProperty("exportController", exportController);



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
