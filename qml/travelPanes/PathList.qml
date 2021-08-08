import QtQuick 2.0
import "../common"

Item {
    TitleTemplate {
        id: title
        leftButtonVisible: true
        leftButtonSource: list.state == "normal_mode" ? "qrc:/images/add_black.png" : "qrc:/images/clear_black.png"
        rightButtonVisible: list.state == "selection_mode"
        rightButtonSource: "qrc:/images/delete_black.png"
        titleText: list.state == "normal_mode" ? "Paths" : "Select Paths"

        onLeftButtonClicked: {
            if (list.state == "normal_mode") {
                // TODO: Add new path
            }
            else {
                list.state = "normal_mode"
            }
        }
        onRightButtonClicked: {
            if (list.state == "selection_mode") {
                // TODO: delete selected paths.
            }
        }
    }
    List {
        id: list
        model: travelController.paths
        anchors {
            top: title.bottom
            left: parent.left
            leftMargin: 20
            right: parent.right
            rightMargin: 20
            bottom: parent.bottom
            bottomMargin: 20
        }
        onListItemClicked: {
            if (state == "normal_mode") {
                if (listItem == travelController.currentPath) {
                    travelController.setCurrentPath(null)
                }
                else {
                    travelController.setCurrentPath(listItem)
                }
            }
        }
    }
}
