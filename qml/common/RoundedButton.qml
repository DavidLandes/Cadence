import QtQuick 2.0

Rectangle {
    id: buttonBase

    property alias text: title.text
    property alias textColor: title.color
    property alias enabled: mouse.enabled

    signal pressed()
    signal released()
    signal clicked()

    height: 40
    width: 100
    radius: height / 2
    opacity: mouse.pressed || !mouse.enabled ? .5 : 1

    Text {
        id: title
        anchors.centerIn: parent
        font {
            pixelSize: 16
            weight: Font.Bold
        }
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onPressed: buttonBase.pressed()
        onReleased: buttonBase.released()
        onClicked: buttonBase.clicked()
    }
}
