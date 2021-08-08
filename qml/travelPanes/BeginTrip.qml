import QtQuick 2.0
import "../common"

Item {
    TitleTemplate {
        id: title
        titleText: "Start a New Trip"

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
