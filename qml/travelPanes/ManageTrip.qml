import QtQuick 2.0
import "../common"

import com.Cadence.Types 1.0

Item {
    property bool isDirty: false
    property Trip selectedTrip
    onSelectedTripChanged: tripName.setText(selectedTrip ? selectedTrip.name : "")
    TitleTemplate {
        id: title
        titleText: selectedTrip ? selectedTrip.name + " Selected" : "Create a New Trip"
    }
    RoundedTextInput {
        id: tripName
        title: "Trip Name:"
        titleColor: "#001256"
        color: "#e9e9e9"
        textColor: "#001256"
        anchors {
            top: title.bottom
            topMargin: 30
            horizontalCenter: parent.horizontalCenter
        }
        onValueChanged: if (value == selectedTrip.name) { isDirty = false } else { isDirty = true }
    }
    RoundedSelectionInput {
        id: pathInput
        property Path thisPath
        Component.onCompleted: {
            thisPath = travelController.getPathFromTrip(selectedTrip)
            value = thisPath.name
        }

        title: thisPath ? "Selected Path:" : "Select a Path:"
        titleColor: "#001256"
        color: "#e9e9e9"
        textColor: "#001256"
        anchors {
            top: tripName.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        onValueChanged: if (value == thisPath.name) { isDirty = false } else { isDirty = true }
    }
    RoundedButton {
        id: submitButton
        text: "Submit"
        textColor: "#001256"
        color: "#e9e9e9"
        enabled: isDirty
        anchors {
            horizontalCenter: parent.horizontalCenter
            horizontalCenterOffset: -width/2 - 10
            top: pathInput.bottom
            topMargin: 30
        }
        onClicked: {
            // TODO: Edit trip data and save the changes.
        }
    }
    RoundedButton {
        id: cancelButton
        text: "Cancel"
        color: "#e9e9e9"
        textColor: "#001256"
        anchors {
            horizontalCenter: parent.horizontalCenter
            horizontalCenterOffset: width/2 + 10
            top: pathInput.bottom
            topMargin: 30
        }
        onClicked: {
            geoController.stop()
        }
    }
}
