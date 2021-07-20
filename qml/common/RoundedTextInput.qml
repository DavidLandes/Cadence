import QtQuick 2.0

Item {
    id: root
    property var placeholderText: "Type something..."
    property alias title: titleText.text
    property alias titleColor: titleText.color
    property alias textColor: displayText.color
    property alias value: data.displayText
    property alias color: container.color
    property bool enabled: true

    function setText(string) {
        data.text = string
    }

    height: titleText.height + container.height + container.anchors.topMargin
    width: container.width

    Text {
        id: titleText
        height: font.pixelSize
        width: container.width
        horizontalAlignment: Text.AlignLeft
        anchors {
            top: root.top
            left: parent.left
            leftMargin: container.radius * .66
        }
        font {
            pixelSize: 15
            weight: Font.Normal
        }
    }

    Rectangle {
        id: container

        height: 40
        width: 250
        radius: height / 2
        anchors {
            top: titleText.bottom
            topMargin: 3
            left: parent.left
            right: parent.right
        }

        Item {
            id: inputItem

            anchors.fill: parent

            Text {
                id: displayText
                height: implicitHeight
                width: parent.width - (anchors.leftMargin * 2)
                text: data.displayText /*|| data.activeFocus*/ ? data.displayText : root.placeholderText.toString()
                opacity: data.displayText ? 1 : .6
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignLeft
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 10
                }
                font {
                    pixelSize: 16
                    weight: Font.Bold
                }
            }
        }

        TextInput {
            id: data
            enabled: root.enabled
            width: displayText.width
            wrapMode: displayText.wrapMode
            anchors {
                verticalCenter: displayText.anchors.verticalCenter
                left: displayText.anchors.left
                leftMargin: displayText.anchors.leftMargin
            }
            cursorVisible: true
            font.pixelSize: displayText.font.pixelSize
            opacity: 0
            z: 10
        }
    }
}
