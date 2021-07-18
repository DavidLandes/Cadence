import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtLocation 5.11
import QtPositioning 5.0

import com.Cadence.Types 1.0

Item {
    RowLayout {
        id: rowlay
        Button {
            id:start
            height: 50
            width: 100
            z:100
            text: "start"
            opacity: geoController.tripState == GeoPositioningController.Active ? .6 : 1
            onClicked: {
                geoController.start()
            }
        }
        Button {
            id:stop
            height: 50
            width: 100
            z:100
            text: "stop"
            opacity: geoController.tripState == GeoPositioningController.Inactive ? .6 : 1
            onClicked: {
                geoController.stop()
            }
        }
    }

    Button {
        id:create
        anchors.top: rowlay.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: 50
        width: 100
        z:100
        text: "create trip"
        onClicked: {
            geoController.createTrip("new trip", new Date(), new Date())
        }
    }
    Button {
        anchors.top: create.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: 50
        width: 100
        z:100
        text: "delete all"
        onClicked: {
            geoController.deleteAllTripData()
        }
    }

    ListView {
        id: tripList
        width: parent.width
        height: parent.height/4
        anchors.bottom: positionlist.top
        model: geoController.trips
        delegate: Text {
            text: modelData.tripName
            font.pixelSize: 20
            width: implicitWidth
            height: 25
            color: modelData.tripId == geoController.currentTrip.tripId ? "cyan" : "black"
            MouseArea {
                anchors.fill: parent
                onPressAndHold: {
                    geoController.deleteTrip(modelData)
                }
                onClicked: { geoController.currentTrip = modelData }
                onPressed: console.log("trip pressed")
            }
        }
    }
    ListView {
        id: positionlist
        width: parent.width
        height: parent.height/4
        anchors.bottom: parent.bottom
        model: geoController.currentTrip ? geoController.currentTrip.positions : []
        delegate: Text {
            text: modelData.coordinate.latitude + ", " + modelData.coordinate.longitude
        }
    }
    Connections {
        target: geoController
        function onCurrentTripChanged() {
            console.log("Current trip changed - length: " + geoController.currentTrip.positions.length)
        }
    }
}
