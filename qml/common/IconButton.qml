import QtQuick 2.0

Item {
    id: iconButton
    signal pressed
    signal released
    signal clicked
    property alias source: icon.source
    property alias preventStealing: mouseArea.preventStealing

    Image {
        id: icon
        anchors {
            fill: parent
        }

        z: 0
        opacity: mouseArea.pressed ? .5 : 1
        fillMode: Image.PreserveAspectFit
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: {
            iconButton.pressed()
        }
        onReleased: {
            iconButton.released()
        }
        onClicked: {
            iconButton.clicked()
        }
    }
}
