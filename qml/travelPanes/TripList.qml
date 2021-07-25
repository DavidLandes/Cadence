import QtQuick 2.0
import "../common"

List {
    leftButtonVisible: true
    leftButtonSource: state == "normal_mode" ? "qrc:/images/arrow_back_black.png" : "qrc:/images/clear_black.png"
    rightButtonVisible: state == "selection_mode"
    rightButtonSource: "qrc:/images/delete_black.png"
    titleText: state == "normal_mode" ? "Trips" : "Select Trips"
    model: travelController.trips   // TODO: display trips based on the selected paths.

    // TODO: if selection_mode, left button cancel, right button delete
    // TODO: if normal_mode, left button back to previous pane, right button NONE

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
