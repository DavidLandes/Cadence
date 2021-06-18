import QtQuick 2.14
import QtQuick.Controls 2.0
import QtQuick.Window 2.14
import QtBluetooth 5.0

import com.Cadence.BluetoothController 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Cadence")

    Text {
        anchors {
            bottom: scanner.top
            horizontalCenter: parent.horizontalCenter
        }
        text: "RPM: " + cadenceInterface.rpm.toString() + "\nMPH: " + cadenceInterface.mph.toString()
    }

    Button {
        id: scanner
        anchors.centerIn: parent
        height: 50
        width: 100
        text: "Scan"
        onClicked: {
            blControl.startDeviceDiscovery()
        }
    }

    Rectangle {
        id: indicator
        height: 25
        width: height
        radius: height/2
        anchors {
            verticalCenter: scanner.verticalCenter
            left: scanner.right
            leftMargin: 10
        }
        states: [
            State {
                name: "Idle"
                when: blControl.state == BluetoothController.Idle
                PropertyChanges {
                    target: indicator
                    color: "red"
                }
            },
            State {
                name: "Scanning"
                when: blControl.state == BluetoothController.Scanning
                PropertyChanges {
                    target: indicator
                    color: "blue"
                }
            },
            State {
                name: "Paired"
                when: blControl.state == BluetoothController.Paired
                PropertyChanges {
                    target: indicator
                    color: "limegreen"
                }
            }
        ]
        SequentialAnimation {
            id: pulse
            running: indicator.state == "Scanning"
            loops: SequentialAnimation.Infinite
            PropertyAnimation {
                target: indicator
                property: "opacity"
                from: 1
                to: .5
                duration: 600
            }
            PropertyAnimation {
                target: indicator
                property: "opacity"
                from: .5
                to: 1
                duration: 600
            }
        }
    }

    DeviceList {
        anchors {
            top: scanner.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
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
