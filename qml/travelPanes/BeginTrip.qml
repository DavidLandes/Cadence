import QtQuick 2.0
import "../common"

import com.Cadence.Types 1.0

Item {
    TitleTemplate {
        id: title
        titleText: travelController.currentTrip ? "Continue " + travelController.currentTrip.name : "Start a New Trip"

    }
    Item {
        anchors {
            top: title.bottom
            left: parent.left
            leftMargin: 20
            right: parent.right
            rightMargin: 20
            bottom: parent.bottom
            bottomMargin: 20
        }
        RoundedButton {
            text: "Start"
            color: "#e9e9e9"
            textColor: "#001256"
            enabled: geoController.state == GeoPositioningController.Inactive
            anchors {
                centerIn: parent
                horizontalCenterOffset: -width/2 - 10
                verticalCenterOffset: -height
            }
            onClicked: {
                if (travelController.currentTrip) {
                    geoController.start()
                }
                else {
                    // TODO: navigates to the create trip pane. for now, just create a test trip & set as active.
                    travelController.createTrip("testtrip", 1, new Date(), new Date(), true)
                }
            }
        }
        RoundedButton {
            text: "Stop"
            color: "#e9e9e9"
            textColor: "#001256"
            enabled: geoController.state == GeoPositioningController.Active
            anchors {
                centerIn: parent
                horizontalCenterOffset: width/2 + 10
                verticalCenterOffset: -height
            }
            onClicked: {
                geoController.stop()
            }
        }
    }
}
