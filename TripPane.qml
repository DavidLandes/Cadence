import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtLocation 5.11
import QtPositioning 5.0

import com.Cadence.Types 1.0

Item {
    Button {
        id:create
        anchors.top: tripList.top
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
            MouseArea {
                anchors.fill: parent
                onPressAndHold: {
                    geoController.deleteTrip(modelData)
                }
                onClicked: { geoController.currentTrip = modelData; geoController.start(modelData) }
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
            console.log("Current trip changed: " + geoController.currentTrip)
        }
    }
}
