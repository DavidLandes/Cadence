#pragma once
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

#include "DeviceInterface.h"
#include "BluetoothController.h"
#include "BluetoothFrames.h"
#include "Device.h"

/* Cadence Sensor Important Info:
 *  Red light - wheel data
 * Blue light - crank data
*/

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Create app configuration file.
    QSettings* settings = new QSettings("./cadence.conf");

    // Register the controller.
    BluetoothController* blControl = new BluetoothController(settings);

    // Register devices.
    DeviceInterface* cadenceInterface = new DeviceInterface(blControl, settings);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Expose properties to qml.
    engine.rootContext()->setContextProperty("blControl", blControl);
    engine.rootContext()->setContextProperty("cadenceInterface", cadenceInterface);

    qmlRegisterUncreatableType<BluetoothController>("com.Cadence.BluetoothController", 1, 0, "BluetoothController", "bl controller reason");
    qmlRegisterUncreatableType<Device>("com.Cadence.Types", 1, 0, "Device", "device reason");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
