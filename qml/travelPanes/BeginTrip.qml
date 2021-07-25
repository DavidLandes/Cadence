import QtQuick 2.0
import "../common"

TitleTemplate {
    titleText: "Start a New Trip"
    sourceComponent: Item {
        RoundedButton {
            text: "Begin"
            color: "#e9e9e9"
            textColor: "#001256"
            anchors {
                centerIn: parent
                horizontalCenterOffset: -width/2 - 10
                verticalCenterOffset: -height
            }
        }
        RoundedButton {
            text: "End"
            color: "#e9e9e9"
            textColor: "#001256"
            anchors {
                centerIn: parent
                horizontalCenterOffset: width/2 + 10
                verticalCenterOffset: -height
            }
        }
    }
}
