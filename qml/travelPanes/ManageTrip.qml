import QtQuick 2.0
import "../common"

import com.Cadence.Types 1.0

Item {
    property bool isDirty: false
    property Trip selectedTrip
    onSelectedTripChanged: {
        tripName.setText(selectedTrip ? selectedTrip.name : "")
        pathInput.thisPath = travelController.getPathFromTrip(selectedTrip)
    }
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
        onValueChanged: if (value == (selectedTrip ? selectedTrip.name : value)) { isDirty = false } else { isDirty = true }
    }
    RoundedSelectionInput {
        id: pathInput
        property Path thisPath

        title: thisPath ? "Selected Path:" : "Select a Path:"
        titleColor: "#001256"
        color: "#e9e9e9"
        textColor: "#001256"
        anchors {
            top: tripName.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        onValueChanged: if (value == (thisPath ? thisPath.name : value)) { isDirty = false } else { isDirty = true }
    }
    RoundedButton {
        id: submitButton
        text: "Submit"
        textColor: "#001256"
        color: "#e9e9e9"
        enabled: isDirty && tripName.value != ""
        anchors {
            horizontalCenter: parent.horizontalCenter
            horizontalCenterOffset: -width/2 - 10
            top: pathInput.bottom
            topMargin: 20
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
