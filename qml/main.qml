import QtQuick 2.14
import QtQuick.Controls 2.0
import QtQuick.Window 2.14
import QtBluetooth 5.0

import com.Cadence.BluetoothController 1.0
import com.Cadence.Types 1.0
import "./common"


ApplicationWindow {
    id: appWindow
    visible: true
    width: 1400 /4
    height: 2960 /4
    title: qsTr("Cadence")
    Rectangle {
        id: header
        color: "#001256"
        width: parent.width
        height: 70
        anchors {
            top: parent.top
        }
    }

    Notifications { id:notificationsOverlay; z: parent.z + 100 }

    Indicator {
        id: mphIndicator
        width: parent.width * .65
        height: width
        anchors {
            top: header.bottom
            topMargin: 25
            horizontalCenter: parent.horizontalCenter
        }

        primaryColor: "red"
        secondaryColor: "grey"
        minimumValue: 0
        maximumValue: 40
        currentValue: Math.round(cadenceInterface.mph)
    }

    RouteMap {
        id: routeMap
        state: "widget"
        trip: travelController.currentTrip ? travelController.currentTrip : null
        z: mphIndicator.z + 5
        anchors {
            top: state != "full_screen" ? mphIndicator.bottom : header.bottom
            topMargin: state != "full_screen" ? 25 : 0
            horizontalCenter: parent.horizontalCenter
        }
    }
}
