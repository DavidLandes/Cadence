import QtQuick 2.0

Rectangle {
    id: drawer

    readonly property real closedY: parent.height - radius
    readonly property real openY: parent.height - drawer.height

    Component.onCompleted: {
        drawer.y = drawer.closedY
    }

    height: parent.height * .4
    width: parent.width
    radius: 25
    color: "white"

    onYChanged: {
        // Limit Y bounds
        if (drawer.y > drawer.closedY) {
            drawer.y = drawer.closedY
        }
        else if (drawer.y < openY) {
            drawer.y = openY
        }
    }

    function open() {
        openAnimation.start()
    }

    function close() {
        closeAnimation.start()
    }

    Rectangle {
        id: dragTab
        height: 5
        width: 40
        radius: height/2
        color: "#e9e9e9"
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: drawer.top
            topMargin: 10
        }
    }

    MouseArea {
        id: touchArea
        property int dragThreshold: 50
        property var initialPressY
        height: 30
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        onPressed: {
            initialPressY = drawer.y
        }
        onReleased: {
            var dragOffset = drawer.y - initialPressY
            if (dragOffset > 0) {
                if (dragOffset > dragThreshold) {
                    close()
                }
                else {
                    open()
                }
            }
            else {
                if (Math.abs(dragOffset) > dragThreshold) {
                    open()
                }
                else {
                    close()
                }
            }
        }
        onPositionChanged: {
            drawer.y += mouse.y
        }
    }

    MouseArea { id: mouseBlocker; anchors.fill: parent; z: touchArea.z - 1; preventStealing: true; }

    Rectangle {
        id: radiusMask
        color: drawer.color
        height: drawer.radius
        anchors {
            bottom: drawer.bottom
            left: drawer.left
            right: drawer.right
        }
    }

    NumberAnimation {
        id: openAnimation
        target: drawer
        property: "y"
        to: openY
        duration: 100
    }

    NumberAnimation {
        id: closeAnimation
        target: drawer
        property: "y"
        to: closedY
        duration: 100
    }
}
