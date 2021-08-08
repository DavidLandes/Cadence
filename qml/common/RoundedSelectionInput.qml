import QtQuick 2.0
import "."

Item {
    id: root
    property var placeholderText: "None selected..."
    property alias title: titleText.text
    property alias titleColor: titleText.color
    property alias textColor: displayText.color
    property alias color: container.color

    property var value: ""
    property bool enabled: true

    signal pressed()
    signal released()
    signal clicked()
    signal clear()

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

        Text {
            id: displayText
            height: implicitHeight
            width: parent.width - (anchors.leftMargin * 2) - button.width
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignLeft
            text: root.value ? root.value : placeholderText.toString()
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 20
            }
            font {
                pixelSize: 16
                weight: Font.Bold
            }
        }

        IconButton {
            id: clearButton
            source: "qrc:/images/clear_black.png"
            height: container.height / 2
            width: height
            z: container.z + 5
            visible: root.value != ""
            enabled: visible
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
            }
            onClicked: {
                root.clear()
            }
        }

        Rectangle {
            id: button
            height: container.height * .9
            width: height
            z: container.z + 5
            radius: container.radius
            color: "#707070"
            opacity: mouse.pressed ? .5 : 1
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: container.height * .05
            }
            Image {
                height: parent.height * .66
                width: height
                source: "qrc:/images/add_white.png"
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
            }
            MouseArea {
                id: mouse
                anchors.fill: parent
                onPressed: root.pressed()
                onReleased: root.released()
                onClicked: root.clicked()
                preventStealing: true
            }
        }
    }
}
