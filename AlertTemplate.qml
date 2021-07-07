import QtQuick 2.0

Rectangle {
    id: template
    property var text: "This is the default alert template"

    width: parent.width * .8
    height: 60
    radius: height/3
    anchors {
        bottom: parent.bottom
        bottomMargin: 20
        horizontalCenter: parent.horizontalCenter
    }

    color: "#c0404040"

    Text {
        anchors {
            centerIn: parent
        }
        width: parent.width * .9
        height: parent.height
        text: template.text
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "white"
        font {
            pixelSize: 15
            weight: Font.ExtraLight
        }
    }

    state: "hidden"

    states: [
        State {
            name: "showing"
            when: template.visible
            PropertyChanges {
                target: template
                opacity: 1
            }
        },
        State {
            name: "hidden"
            when: !template.visible
            PropertyChanges {
                target: template
                opacity: 0
            }
        }
    ]

    transitions: [
        Transition {
            from: "hidden"
            to: "showing"
            NumberAnimation {
                target: template
                property: "opacity"
                duration: 400
                easing.type: Easing.InOutQuad
            }
        },
        Transition {
            from: "showing"
            to: "hidden"
            NumberAnimation {
                target: template
                property: "opacity"
                duration: 400
                easing.type: Easing.InOutQuad
            }
        }
    ]
}
