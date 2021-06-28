import QtQuick 2.0
import QtQuick.Controls 2.0

import com.Cadence.BluetoothController 1.0
import "./common"

Rectangle {
    Rectangle {
        id: header
        height: 60
        width: parent.width
        z: parent.z + 5
        color: "lightgrey"
        anchors {
            top: parent.top
        }
        Text {
            id: headerText
            text: "Available Devices"
            anchors {
                left: parent.left
                leftMargin: 30
                verticalCenter: parent.verticalCenter
            }
        }
        BusyIndicator {
            id: busy
            primaryColor: "red"
            secondaryColor: "grey"
            anchors {
                left: headerText.right
                leftMargin: 10
                verticalCenter: headerText.verticalCenter
            }
            Connections {
                target: blControl
                function onStateChanged(state) {
                    if (state == BluetoothController.Scanning)
                        busy.start()
                    else
                        busy.stop()
                }
            }
        }
        Button {
            id: scanner
            anchors {
                right: parent.right
                rightMargin: 30
                verticalCenter: busy.verticalCenter
            }
            height: 50
            width: 100
            text: "Scan"
            onClicked: {
                blControl.startDeviceDiscovery()
            }
        }
    }
    DeviceList {
        id: devices
        anchors {
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }
}
