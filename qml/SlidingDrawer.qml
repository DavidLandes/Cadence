import QtQuick 2.0

Rectangle {
    id: drawer

    property alias sourceComponent: contentLoader.sourceComponent

    readonly property real closedY: parent.height
    readonly property real openY: parent.height - drawer.height

    Component.onCompleted: {
        drawer.y = drawer.closedY
    }

    height: parent.height * .5
    width: parent.width
    radius: 15
    color: "white"
    visible: false

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

    Loader {
        id: contentLoader
        anchors {
            top: touchArea.bottom
            topMargin: 5
            left: parent.left
            leftMargin: 5
            right: parent.right
            rightMargin: 5
            bottom: parent.bottom
            bottomMargin: 10
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

    SequentialAnimation {
        id: openAnimation
        ScriptAction {
            script: drawer.visible = true
        }
        NumberAnimation {
            target: drawer
            property: "y"
            to: openY
            duration: 100
        }
    }
    SequentialAnimation {
        id: closeAnimation
        NumberAnimation {
            target: drawer
            property: "y"
            to: closedY
            duration: 100
        }
        ScriptAction {
            script: drawer.visible = false
        }
    }
}
