import QtQuick 2.0
import QtQml 2.0

import com.Cadence.Types 1.0

Rectangle {
    id: template

    function getText() {
        if (notifications.currentAlert)
        {
            switch(notifications.currentAlert.alertType)
            {
            case NotificationData.Alert_Test:
                return "This is a test alert"
            case NotificationData.Alert_Test2:
                return "This is a test alert222222222"
            default:
                return ""
            }
        }
        else
        {
            return ""
        }
    }

    property var timeout: 3500

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
        text: template.getText()
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "white"
        font {
            pixelSize: 15
            weight: Font.ExtraLight
        }
    }

    Timer {
        id: timeoutTimer
        repeat: false
        interval: template.timeout
        onTriggered: {
            // Hide & remove the current alert.
            template.state = "hidden"
        }
    }

    Connections {
        target: notifications
        function onCurrentAlertChanged(alert) {
            if (alert)
            {
                template.state = "showing"
                timeoutTimer.start()
            }
            else
            {
                template.state = "hidden"
                timeoutTimer.stop()
            }
        }
    }

    // WARNING: Changing this value from outside components could cause some issues, such as removing extra alerts from the queue.
    state: "hidden"

    states: [
        State {
            name: "showing"
            PropertyChanges {
                target: template
                opacity: 1
            }
        },
        State {
            name: "hidden"
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
            SequentialAnimation {
                NumberAnimation {
                    target: template
                    property: "opacity"
                    duration: 400
                    easing.type: Easing.InOutQuad
                }
                ScriptAction {
                    script: {
                        notifications.removeNotification(notifications.currentAlert)
                    }
                }
            }
        }
    ]
}
