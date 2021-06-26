import QtQuick 2.0
import QtQuick.Controls 2.0
import QtBluetooth 5.0

ListView {
    id: deviceList
    model: blControl.discoveredDeviceNames
    delegate: Rectangle {
        height: 60
        width: parent.width * .8
        color: "pink"
        Text {
            height: parent.height
            width: parent.width
            anchors.left: parent.left
            font {
                pixelSize: 24
            }
            color: modelData == cadenceInterface.device.name ? "blue" : "black"
            text: modelData
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                blControl.setCadenceDevice(modelData)
            }
        }
    }

    Rectangle {
        id: background
        color: "lightgrey"
        anchors.fill: parent
        z: deviceList.z-1
    }
}
