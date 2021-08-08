import QtQuick 2.0
import "../common"

Item {
    TitleTemplate {
        id: title
        leftButtonVisible: true
        leftButtonSource: list.state == "normal_mode" ? "qrc:/images/arrow_back_black.png" : "qrc:/images/clear_black.png"
        rightButtonVisible: list.state == "selection_mode"
        rightButtonSource: "qrc:/images/delete_black.png"
        titleText: list.state == "normal_mode" ? "Trips" : "Select Trips"

        onLeftButtonClicked: {
            if (list.state == "normal_mode") {
                travelController.setCurrentPath(null)
            }
            else {
                list.state = "normal_mode"
            }
        }
        onRightButtonClicked: {
            if (list.state == "selection_mode") {
                // TODO: Delete selected trips
            }
        }
    }
    List {
        id: list
        model: travelController.trips
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
                if (listItem == travelController.currentTrip) {
                    travelController.setCurrentTrip(null)
                }
                else {
                    travelController.setCurrentTrip(listItem)
                }
            }
        }
    }
}
