#pragma once
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

#include "./header/misc.h"
#include "./header/DeviceInterface.h"
#include "./header/BluetoothController.h"
#include "./header/BluetoothFrames.h"
#include "./header/Device.h"
#include "./header/DbController.h"
#include "./header/Path.h"
#include "./header/PathDao.h"
#include "./header/Trip.h"
#include "./header/TripDao.h"
#include "./header/Position.h"
#include "./header/PositionDao.h"
#include "./header/GeoPositioningController.h"
#include "./header/NotificationData.h"
#include "./header/NotificationController.h"
#include "./header/ExportController.h"
#include "./header/TravelController.h"
#include "./header/Application.h"

/* Cadence Sensor Important Info:
 *  Red light - wheel data
 * Blue light - crank data
*/

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Register application.
    Application* application = new Application();

    // Create app configuration file.
    QSettings* settings = new QSettings("./cadence.conf");

    // Register controllers.
    BluetoothController* blControl = new BluetoothController(settings);
    DbController* databaseController = new DbController();

    // Register devices.
    DeviceInterface* cadenceInterface = new DeviceInterface(blControl, settings);

    // Register positioning controller.
    GeoPositioningController* geoController = new GeoPositioningController(cadenceInterface);

    // Register travel controller.
    TravelController* travelController = new TravelController(databaseController, geoController);

    // Register notification controller.
    NotificationController* notifications = new NotificationController();

    ExportController* exportController = new ExportController();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    // Register types to qml.
    qmlRegisterUncreatableType<BluetoothController>("com.Cadence.BluetoothController", 1, 0, "BluetoothController", "bl controller reason");
    qmlRegisterUncreatableType<Device>("com.Cadence.Types", 1, 0, "Device", "device reason");
    qmlRegisterUncreatableType<Path>("com.Cadence.Types", 1, 0, "Path", "path reason");
    qmlRegisterUncreatableType<Trip>("com.Cadence.Types", 1, 0, "Trip", "trip reason");
    qmlRegisterUncreatableType<Position>("com.Cadence.Types", 1, 0, "Position", "position reason");
    qmlRegisterUncreatableType<NotificationController>("com.Cadence.Types", 1, 0, "NotificationController", "notification controller reason");
    qmlRegisterUncreatableType<NotificationData>("com.Cadence.Types", 1, 0, "NotificationData", "notification data reason");
    qmlRegisterUncreatableType<GeoPositioningController>("com.Cadence.Types", 1, 0, "GeoPositioningController", "geo positioning controller reason");
    qmlRegisterUncreatableType<TravelController>("com.Cadence.Types", 1, 0, "TravelController", "travel controller reason");

    // Expose properties to qml.
    engine.rootContext()->setContextProperty("blController", blControl);
    engine.rootContext()->setContextProperty("cadenceInterface", cadenceInterface);
    engine.rootContext()->setContextProperty("geoController", geoController);
    engine.rootContext()->setContextProperty("travelController", travelController);
    engine.rootContext()->setContextProperty("notifications", notifications);
    engine.rootContext()->setContextProperty("exportController", exportController);
    engine.rootContext()->setContextProperty("application", application);



    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
