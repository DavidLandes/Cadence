import QtQuick 2.0

Item {
    property alias titleText: title.text
    property alias sourceComponent: content.sourceComponent

    property alias leftButtonVisible: leftButton.visible
    property alias leftButtonSource: leftButton.source

    property alias rightButtonVisible: rightButton.visible
    property alias rightButtonSource: rightButton.source

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

    Loader {
        id: content
        anchors {
            top: title.bottom
            topMargin: 10
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }
}
