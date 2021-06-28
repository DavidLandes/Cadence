import QtQuick 2.0
import QtQuick.Controls 2.0
import QtBluetooth 5.0

import com.Cadence.Types 1.0

ListView {
    id: deviceList
    model: blControl.discoveredDevices
    delegate: Rectangle {
        id: deviceDelegate
        property bool connected: cadenceInterface.device && modelData.name() == cadenceInterface.device.name()
        height: 60
        width: parent.width * .8
        anchors {
            horizontalCenter: parent.horizontalCenter
        }
        color: "transparent"
        clip: true
        Text {
            height: parent.height
            width: parent.width
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
            }
            font {
                pixelSize: 24
            }
            verticalAlignment: Text.AlignVCenter
            color: deviceDelegate.connected ? "lightblue" : "black"
            text: modelData.name()
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                cadenceInterface.setDevice(modelData)
            }
        }
    }
}
