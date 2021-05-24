import QtQuick 2.14
import QtQuick.Controls 2.0
import QtQuick.Window 2.14
import QtBluetooth 5.0
import com.cadence.Blue 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Cadence")

    Button {
        anchors.centerIn: parent
        height: 50
        width: 100
        text: "Scan"
        onClicked: {
            blControl.startDeviceDiscovery()
        }
    }

//    Text {
//        id: count
//        text: bluetooth.state
//        anchors.centerIn: parent
//        z:665156
//    }
//    ListView {
//        anchors.fill: parent
//        model: bluetooth.deviceNames

//        delegate:  Text {
//            height: 50
//            width: parent.width
//            text: modelData
//        }
//    }

//    Connections {
//        target: bluetooth
//        function onDevicesChanged() {
//            console.log(bluetooth.devices)
//        }
//    }
}
