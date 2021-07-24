import QtQuick 2.0
import "../common"

ListPane {
    leftButtonVisible: true
    leftButtonSource: state == "normal_mode" ? "qrc:/images/add_black.png" : "qrc:/images/clear_black.png"
    rightButtonVisible: state == "selection_mode"
    rightButtonSource: "qrc:/images/delete_black.png"
    titleText: state == "normal_mode" ? "Paths" : "Select Paths"
    model: travelController.paths

    // TODO: if selection_mode, left button cancel, right button delete
    // TODO: if normal_mode, left button add, right button NONE

    onLeftButtonClicked: {
        if (state == "normal_mode") {

        }
        else {

        }
    }
    onRightButtonClicked: {
        if (state == "normal_mode") {

        }
        else {

        }
    }
    onListItemClicked: {
        if (state == "normal_mode") {

        }
    }
}
