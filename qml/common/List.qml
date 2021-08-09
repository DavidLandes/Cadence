import QtQuick 2.0

Item {
    id: listPane

    property alias model: list.model
    property bool selectionModeEnabled: true
    property var selectedItems: []

    signal listItemClicked(var listItem)

    Rectangle {
        id: listContainter
        color: "#e9e9e9"
        radius: 0
        anchors {
            fill: parent
        }

        ListView {
            id: list
            clip: true
            anchors.fill: parent
            delegate: Element {
                // TODO: find a way to change opacity or color when clicked, while still being within the bounds.
                height: 55
                width: parent.width
                text: modelData.name
                hasUnderline: list.model.length - 1 == index ? false : true
                underlineColor: "#707070"
                onClicked: {
                    if (listPane.state == "selection_mode") {
                        listPane.selectedItems.push(modelData)
                    }
                    else if (listPane.state == "normal_mode") {
                        listPane.listItemClicked(modelData)
                    }
                }
                onPressAndHold: {
                    if (listPane.selectionModeEnabled) {
                        listPane.state = "selection_mode"
                        listPane.selectedItems.push(modelData)
                    }
                }
            }
        }
    }

    state: "normal_mode"

    states: [
        State {
            name: "normal_mode"
            PropertyChanges {
                target: listPane
                selectedItems: []
            }
        },
        State {
            name: "selection_mode"
        }
    ]
}
