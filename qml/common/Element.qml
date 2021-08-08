import QtQuick 2.0

Rectangle {
    id: element

    property bool hasMore: false
    property bool hasUnderline: false
    property alias text: title.text
    property alias textColor: title.color
    property alias underlineColor: underline.color

    signal clicked()
    signal pressed()
    signal released()
    signal pressAndHold()

    height: 60
    width: parent.width
   // color: mouse.pressed ? "#707070" : "#e9e9e9"

    Text {
        id: title
        opacity: mouse.pressed ? .5 : 1
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 20
        }
        font {
            pixelSize: 16
            weight: Font.Normal
        }
    }

    Image {
        id: hasMoreIcon
        visible: element.hasMore
        height: parent.height * .4
        width: height
        source: "qrc:/images/chevron_right_black.png"
        fillMode: Image.PreserveAspectFit
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 10
        }
    }

    Rectangle {
        id: underline
        visible: element.hasUnderline
        width: parent.width
        height: 1
        anchors.bottom: parent.bottom
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: element.clicked()
        onPressed: element.pressed()
        onReleased: element.released()
        onPressAndHold: element.pressAndHold()
    }
}
