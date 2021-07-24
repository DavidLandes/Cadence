import QtQuick 2.0

Item {
    id: listPane

    property alias titleText: title.text
    property alias model: list.model
    property bool selectionModeEnabled: true
    property var selectedItems: []

    property alias leftButtonVisible: leftButton.visible
    property alias leftButtonSource: leftButton.source

    property alias rightButtonVisible: rightButton.visible
    property alias rightButtonSource: rightButton.source

    signal listItemClicked(var listItem)
    signal leftButtonClicked()
    signal rightButtonClicked()

    IconButton {
        id: leftButton
        height: 35
        width: height
        anchors {
            top: parent.top
            left: parent.left
            leftMargin: 20
        }
        onClicked: leftButtonClicked()
    }

    Text {
        id: title
        color: "#001256"
        width: implicitWidth
        height: 20
        anchors {
            top: parent.top
            topMargin: 5
            horizontalCenter: parent.horizontalCenter
        }
        font {
            pixelSize: 20
            weight: Font.Bold
        }
    }

    IconButton {
        id: rightButton
        height: 35
        width: height
        anchors {
            top: parent.top
            right: parent.right
            rightMargin: 20
        }
        onClicked: rightButtonClicked()
    }

    Rectangle {
        id: listContainter
        color: "#e9e9e9"
        radius: 10
        anchors {
            top: title.bottom
            topMargin: 20
            left: parent.left
            leftMargin: leftButton.anchors.leftMargin + (leftButton.width / 2)
            right: parent.right
            rightMargin: rightButton.anchors.rightMargin + (rightButton.width / 2)
            bottom: parent.bottom
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
                color: "transparent"
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
