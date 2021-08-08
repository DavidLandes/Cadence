import QtQuick 2.0
import "../common"

import com.Cadence.Types 1.0

Item {
    property bool isDirty: false
    property Path selectedPath
    onSelectedPathChanged: pathName.setText(selectedPath ? selectedPath.name : "")
    TitleTemplate {
        id: title
        titleText: selectedPath ? selectedPath.name + " Selected" : "Create a New Path"
    }
    RoundedTextInput {
        id: pathName
        title: "Path Name:"
        titleColor: "#001256"
        color: "#e9e9e9"
        textColor: "#001256"
        anchors {
            top: title.bottom
            topMargin: 30
            horizontalCenter: parent.horizontalCenter
        }
        onValueChanged: if (value == (selectedPath ? selectedPath.name : value)) { isDirty = false } else { isDirty = true }
    }
    RoundedButton {
        text: "Submit"
        textColor: "#001256"
        color: "#e9e9e9"
        enabled: isDirty && pathName.value != ""
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: pathName.bottom
            topMargin: 30
        }
        onClicked: {
            // TODO: Edit Path data and save the changes.
        }
    }
}
