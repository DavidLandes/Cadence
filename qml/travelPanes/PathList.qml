import QtQuick 2.0
import "../common"

TitleTemplate {
    leftButtonVisible: true
    leftButtonSource: list.state == "normal_mode" ? "qrc:/images/add_black.png" : "qrc:/images/clear_black.png"
    rightButtonVisible: list.state == "selection_mode"
    rightButtonSource: "qrc:/images/delete_black.png"
    titleText: list.state == "normal_mode" ? "Paths" : "Select Paths"

    // TODO: if selection_mode, left button cancel, right button delete
    // TODO: if normal_mode, left button add, right button NONE

    onLeftButtonClicked: {
        if (list.state == "normal_mode") {

        }
        else {

        }
    }
    onRightButtonClicked: {
        if (list.state == "normal_mode") {

        }
        else {

        }
    }

    sourceComponent: List {
        id: list
        model: travelController.path
        anchors.fill: parent
        onListItemClicked: {
            if (state == "normal_mode") {

            }
        }
    }
}
