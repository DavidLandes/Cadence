import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import com.Cadence.Types 1.0

Item {
    Button {
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
                onClicked: geoController.start(modelData)
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
            text: modelData.coordinate.latitude
        }
    }
}
