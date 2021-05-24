#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

#include "BluetoothInterface.h"
#include "BluetoothController.h"
#include "BleMessage.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    enum class Type {
        asdf
    };

    QSettings* settings = new QSettings("./cadence.conf");
    BluetoothInterface* bl = new BluetoothInterface();
    BluetoothController* blControl = new BluetoothController(bl, settings);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("blControl", blControl);
    engine.rootContext()->setContextProperty("bluetooth", bl);
    qmlRegisterUncreatableType<BluetoothInterface>("com.cadence.Blue", 1, 0, "Bluetooth", "");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
